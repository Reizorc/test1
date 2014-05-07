#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "src/Map.h"
#include "src/Title.h"
#include "print.h"

#define NB_BLOCS_L 100
#define NB_BLOCS_H 100

#define NB_BLOCS_X 11
#define NB_BLOCS_Y 9

sf::View view(sf::Vector2f(NB_BLOCS_X*64/2, NB_BLOCS_Y*64/2), sf::Vector2f(NB_BLOCS_X*64, NB_BLOCS_Y*64));

sf::Font font;
sf::Sprite grass;
sf::Sprite stone;

Entity* perso; // seul entity dont on garde une reference directement

sf::Texture tex_spider;
sf::Texture tex_perso;

Map* gamemap;

int persoX;
int persoY;

void affiche(sf::RenderWindow& app, Map* gamemap);
void scrolling(int screenX,int screenY);
sf::Vector2i getPersoTitle(sf::Sprite perso);
void Fov(int x1, int y1, int const x2, int const y2, int max, Map* gamemap);

int main()
{

    srand (time(NULL));
    sf::RenderWindow app(sf::VideoMode(NB_BLOCS_X*64 , NB_BLOCS_Y*64), "TILE MAP!!)");

    gamemap = new Map(NB_BLOCS_H, NB_BLOCS_L);

    print aff(app);

    font.loadFromFile("arial.ttf");

    int id;

    persoX = 6;
    persoY = 5;

    aff.registerSprite("perso.png");
    aff.registerSprite("spider.png");
    aff.registerSprite("stone.png");
    aff.registerSprite("grass.png");

    perso = new Entity();
    perso->setSprite("perso");
    perso->setParent(gamemap->map[6][5]);

    Entity* spider = new Entity();
    spider->setSprite("spider");

    gamemap->map[6][6]->entity.push_back(spider);

    sf::Vector2f position(NB_BLOCS_X*64/2,NB_BLOCS_Y*64/2);

    while (app.isOpen())
    {
        int posX = 7;
        int posY = 7;

        //scrolling(NB_BLOCS_X*64/2,NB_BLOCS_Y*64/2);


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
                    if(persoX > 5)
                    {
                        if(!gamemap->map[persoX-1][persoY]->cantWalk){
                           perso->moveTo(gamemap, perso->parent->pos.x-1, perso->parent->pos.y);
                           persoX--;
                        }

                    }
                    break;

                case sf::Keyboard::Right :
                    if(posX <= NB_BLOCS_L*64 +64)
                        if(!gamemap->map[persoX+1][persoY]->cantWalk){
                           perso->moveTo(gamemap, perso->parent->pos.x+1, perso->parent->pos.y);
                           persoX++;
                        }
                    break;

                case sf::Keyboard::Up :
                    if(persoY > 5)
                        if(!gamemap->map[persoX][persoY-1]->cantWalk){
                            perso->moveTo(gamemap, perso->parent->pos.x, perso->parent->pos.y-1);
                            persoY--;
                        }
                    break;

                case sf::Keyboard::Down :
                    if(posY < NB_BLOCS_H*64 -64)
                        if(!gamemap->map[persoX][persoY+1]->cantWalk){
                            perso->moveTo(gamemap, perso->parent->pos.x, perso->parent->pos.y+1);
                            persoY++;
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
            if(gamemap->map[x][y]->visible)
            {
               gamemap->map[x][y]->visible = 0;
               gamemap->map[x][y]->discoverd = 1;
            }

        }
    }

        int dist = 3;

        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(persoX, persoY, 0, x, dist, gamemap);
        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(persoX, persoY, NB_BLOCS_H-1, x, dist, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(persoX, persoY, x, 0, dist, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(persoX, persoY, x, NB_BLOCS_L-1, dist, gamemap);

        app.clear();


        aff.affiche(gamemap->getMap(persoX-5, persoY-4, persoX+6, persoY+5));

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

    for(int x = 0; x < gamemap->x; x++)
    {
        for( int y = 0; y < gamemap->y; y++)
        {
            Title* title = gamemap->map[x][y];
            if(title->visible || title->discoverd)
            {
                if(title->discoverd && !title->visible)
                {
                    grass.setColor(sf::Color(255, 255, 255, 128));
                    stone.setColor(sf::Color(255, 255, 255, 128));
                }
                else
                {
                    grass.setColor(sf::Color(255, 255, 255, 255));
                    stone.setColor(sf::Color(255, 255, 255, 255));
                }
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
    //app.draw(perso);
    //app.draw(spider);
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
