#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "src/Map.h"
#include "src/Title.h"

#define NB_BLOCS_L 100
#define NB_BLOCS_H 100

#define NB_BLOCS_X 11
#define NB_BLOCS_Y 9

sf::View view(sf::Vector2f(NB_BLOCS_X*64/2, NB_BLOCS_Y*64/2), sf::Vector2f(NB_BLOCS_X*64, NB_BLOCS_Y*64));

sf::Font font;
sf::Sprite grass;
sf::Sprite stone;
sf::Sprite perso;
sf::Sprite spider;

sf::Texture tex_spider;
sf::Texture tex_perso;

Map* gamemap;

void affiche(sf::RenderWindow& app, Map* gamemap);
void scrolling(int screenX,int screenY);
sf::Vector2i getPersoTitle(sf::Sprite perso);
void Fov(int x1, int y1, int const x2, int const y2, int max, Map* gamemap);

int main()
{

    srand (time(NULL));
    sf::RenderWindow app(sf::VideoMode(NB_BLOCS_X*64 , NB_BLOCS_Y*64), "TILE MAP!!)");

    font.loadFromFile("arial.ttf");

    tex_perso.loadFromFile("res/img/perso.png");
    perso.setTexture(tex_perso);
    perso.setPosition(0,0);

    tex_spider.loadFromFile("res/img/spider.png");
    spider.setTexture(tex_spider);
    spider.setPosition(64*5,64*6);

    gamemap = new Map(NB_BLOCS_H, NB_BLOCS_L);

    sf::Vector2f position(NB_BLOCS_X*64/2,NB_BLOCS_Y*64/2);

    while (app.isOpen())
    {
        int posX = perso.getPosition().x;
        int posY = perso.getPosition().y;

        scrolling(NB_BLOCS_X*64/2,NB_BLOCS_Y*64/2);


        sf::Event event;
        while (app.pollEvent(event))
        {

            switch (event.type) // Type de l'évènement
            {
            case sf::Event::Closed : // Bouton de fermeture
                app.close();
                break;

            case sf::Event::KeyPressed : // Appui sur une touche du clavier
            {
                switch (event.key.code) // La touche qui a été appuyée
                {
                case sf::Keyboard::Escape : // Echap
                    app.close();
                    break;

                case sf::Keyboard::Left :
                    if(posX >= NB_BLOCS_L/64)
                    {
                        if(!gamemap->map[getPersoTitle(perso).x-1][getPersoTitle(perso).y]->cantWalk){
                            perso.move(-64,0);
                        }

                    }
                    break;

                case sf::Keyboard::Right :
                    if(posX <= NB_BLOCS_L*64 +64)
                        if(!gamemap->map[getPersoTitle(perso).x+1][getPersoTitle(perso).y]->cantWalk){
                            perso.move(64,0);
                        }
                    break;

                case sf::Keyboard::Up :
                    if(posY >= NB_BLOCS_H/64)
                        if(!gamemap->map[getPersoTitle(perso).x][getPersoTitle(perso).y-1]->cantWalk){
                            perso.move(0,-64);
                        }
                    break;

                case sf::Keyboard::Down :
                    if(posY < NB_BLOCS_H*64 -64)
                        if(!gamemap->map[getPersoTitle(perso).x][getPersoTitle(perso).y+1]->cantWalk){
                            perso.move(0,64);

                        }
                    break;
                default :
                    break;
                }
            }
            break;

            default :
                break;
            }

        }

            for(int x = 0; x < NB_BLOCS_H; x++)
    {
        for(int y = 0; y < NB_BLOCS_L; y++)
        {
            gamemap->map[x][y]->visible = 0;
        }
    }

        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 0, x, 3, gamemap);
        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, NB_BLOCS_H-1, x, 3, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, x, 0, 3, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, x, NB_BLOCS_L-1, 3, gamemap);

        app.clear();


        affiche(app, gamemap);

        app.setView(view);

        app.display();

    }


    return EXIT_SUCCESS;
}

sf::Vector2i getPersoTitle(sf::Sprite sprite)
{
    return sf::Vector2i(sprite.getPosition().x/64, sprite.getPosition().y/64);
}

void affiche(sf::RenderWindow &app, Map* gamemap)
{

    sf::Texture tex_grass;
    tex_grass.loadFromFile("res/img/grass.png");
    grass.setTexture(tex_grass);


    sf::Texture tex_stone;
    tex_stone.loadFromFile("res/img/stone.png");
    stone.setTexture(tex_stone);

    for(int x = 0; x < NB_BLOCS_H; x++)
    {
        for( int y = 0; y < NB_BLOCS_L; y++)
        {
            Title* title = gamemap->map[x][y];
            if(title->visible)
            {
                if(title->ID == 0)
                {
                    grass.setPosition(64*(x+1)-64, 64*(y+1)-64);
                    app.draw(grass);
                }
                if(title->ID == 1)
                {
                    stone.setPosition(64*(x+1)-64, 64*(y+1)-64);
                    app.draw(stone);
                }
            }

        }
    }
    app.draw(perso);
    app.draw(spider);
}

void Fov(int x1, int y1, int const x2, int const y2, int max, Map* gamemap)
{

    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    gamemap->map[x1][y1]->visible = 1;

    int x = 0;

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)
        {
            x++;
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            gamemap->map[x1][y1]->visible = 1;
            if(gamemap->map[x1][y1]->opaque || x == max)
                return;
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            x++;
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            gamemap->map[x1][y1]->visible = 1;
            if(gamemap->map[x1][y1]->opaque || x == max)
                return;
        }
    }
}
void scrolling(int screenX,int screenY){
        sf::Vector2f position(screenX,screenY);

        if(perso.getPosition().x +10 > screenX)
            position.x = perso.getPosition().x + 10;
        else
            position.x = screenX;
        if(perso.getPosition().y +10 > screenY)
            position.y = perso.getPosition().y + 10;
        else
            position.y = screenY;

        view.setCenter(position);

}


