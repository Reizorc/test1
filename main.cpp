#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define NB_BLOCS_L 9
#define NB_BLOCS_H 12

sf::Font font;
sf::Sprite grass;
sf::Sprite stone;
sf::Sprite perso;
sf::Texture tex_perso;

struct Title
{
    sf::Vector2i pos;
    sf::Vector2i realPos;
    int cantWalk;
    int ID;
    int visible;
    int opaque;

};

void affiche(sf::RenderWindow& app, Title* gamemap[NB_BLOCS_H][NB_BLOCS_L]);
sf::Vector2i getPersoTitle(sf::Sprite perso);
void Fov(int x1, int y1, int const x2, int const y2, Title* gamemap[NB_BLOCS_H][NB_BLOCS_L]);

int main()
{

    srand (time(NULL));

    sf::RenderWindow app(sf::VideoMode(NB_BLOCS_H*64, NB_BLOCS_L*64), "TILE MAP!!)");

    font.loadFromFile("arial.ttf");

    tex_perso.loadFromFile("res/img/perso.png");
    perso.setTexture(tex_perso);
    perso.setPosition(64*3,64*4);



    Title* gamemap[NB_BLOCS_H][NB_BLOCS_L];
    int* gametitle[NB_BLOCS_H][NB_BLOCS_L]=
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    for(int x = 0; x < NB_BLOCS_H; x++)
    {
        for(int y = 0; y < NB_BLOCS_L; y++)
        {
            gamemap[x][y] = new Title;
            Title* title = gamemap[x][y];
            title->ID = gametitle[x][y]; //rand() % 2 + 0; // rand() % max + min
            title->pos = sf::Vector2i(x, y);
            title->visible = 0;
            if(title->ID == 1)
            {
                title->cantWalk = 1;
                title->opaque = 1;
            }
            else
            {
                title->cantWalk = 0;
                title->opaque = 0;
            }
        }
    }


    while (app.isOpen())
    {
        int posX = perso.getPosition().x;
        int posY = perso.getPosition().y;
        int posXstone = stone.getPosition().x;
        int posYstone = stone.getPosition().y;

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
                    if(posX >= NB_BLOCS_H/64 +64)
                    {
                        if(!gamemap[getPersoTitle(perso).x-1][getPersoTitle(perso).y]->cantWalk)
                            perso.move(-64,0);
                    }
                    break;

                case sf::Keyboard::Right :
                    if(posX <= NB_BLOCS_L*64 +64)
                        if(!gamemap[getPersoTitle(perso).x+1][getPersoTitle(perso).y]->cantWalk)
                            perso.move(64,0);
                    break;

                case sf::Keyboard::Up :
                    if(posY >= NB_BLOCS_H/64 +64)
                        if(!gamemap[getPersoTitle(perso).x][getPersoTitle(perso).y-1]->cantWalk)
                            perso.move(0,-64);
                    break;

                case sf::Keyboard::Down :
                    if(posY < NB_BLOCS_L*64 -64)
                        if(!gamemap[getPersoTitle(perso).x][getPersoTitle(perso).y+1]->cantWalk)
                            perso.move(0,64);
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
            gamemap[x][y]->visible = 0;
        }
    }

        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 0, x, gamemap);
        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, NB_BLOCS_H-1, x, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, x, 0, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, x, NB_BLOCS_L-1, gamemap);

//        Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 9, 9, gamemap);
//        Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 0, 1, gamemap);
//        Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 0, 2, gamemap);
//        Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 0, 3, gamemap);
//        Fov(getPersoTitle(perso).x, getPersoTitle(perso).y, 0, 4, gamemap);


        app.clear();
        affiche(app, gamemap);

        app.display();

    }


    return EXIT_SUCCESS;
}

sf::Vector2i getPersoTitle(sf::Sprite sprite)
{
    return sf::Vector2i(sprite.getPosition().x/64, sprite.getPosition().y/64);
}

void affiche(sf::RenderWindow &app, Title* gamemap[NB_BLOCS_H][NB_BLOCS_L])
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
            Title* title = gamemap[x][y];
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
}

void Fov(int x1, int y1, int const x2, int const y2, Title* gamemap[NB_BLOCS_H][NB_BLOCS_L])
{

    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    gamemap[x1][y1]->visible = 1;

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            gamemap[x1][y1]->visible = 1;
            if(gamemap[x1][y1]->opaque)
                return;
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            gamemap[x1][y1]->visible = 1;
            if(gamemap[x1][y1]->opaque)
                return;
        }
    }
}


