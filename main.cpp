#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "src/Map.h"
#include "src/Title.h"
#include "print.h"
#include "define.h"
#include "horloge.h"

sf::Font font;
sf::Sprite grass;
sf::Sprite stone;

Entity* perso; // seul entity dont on garde une reference directement

sf::Texture tex_spider;
sf::Texture tex_perso;

Map* gamemap;

Horloge horloge;

int persoX;
int persoY;

sf::Vector2i getPersoTitle(sf::Sprite perso);
void Fov(int x1, int y1, int const x2, int const y2, int max, Map* gamemap);

int main()
{

    srand (time(NULL));
    sf::RenderWindow app(sf::VideoMode((float)((NB_BLOCS_X-1)*BLOCS_SIZE), (float)((NB_BLOCS_Y-1)*BLOCS_SIZE)), "TILE MAP!!)");

    gamemap = new Map(NB_BLOCS_H, NB_BLOCS_L);

    print aff(app);

    font.loadFromFile("arial.ttf");

    int id;

    persoX = DIST_FROM_UP+10;
    persoY = DIST_FROM_LEFT+10;

    aff.registerSprite("perso.png");
    aff.registerSprite("spider.png");
    aff.registerSprite("stone.png");
    aff.registerSprite("grass.png");

    perso = new Entity();
    perso->setSprite("perso");
    perso->setParent(gamemap->map[persoX][persoY]);
    perso->nextTick = 1000;
    horloge.add(perso);

    Entity* spider = new Entity();
    spider->setSprite("spider");
    spider->setParent(gamemap->map[persoX+1][persoY+1]);
    spider->nextTick = 3000;
    horloge.add(spider);

    sf::Vector2f position(NB_BLOCS_X*BLOCS_SIZE/2,NB_BLOCS_Y*BLOCS_SIZE/2);

    std::cout << NB_BLOCS_X*BLOCS_SIZE << std::endl;

    while (app.isOpen())
    {
        int posX = 7;
        int posY = 7;

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
                           perso->nextTick = 1000;
                           horloge.tick();
                           persoX--;
                        }

                    }
                    break;

                case sf::Keyboard::Right :
                    if(persoX < NB_BLOCS_L-5)
                        if(!gamemap->map[persoX+1][persoY]->cantWalk){
                           perso->moveTo(gamemap, perso->parent->pos.x+1, perso->parent->pos.y);
                           perso->nextTick = 1000;
                           horloge.tick();
                           persoX++;
                        }
                    break;

                case sf::Keyboard::Up :
                    if(persoY > 5)
                        if(!gamemap->map[persoX][persoY-1]->cantWalk){
                            perso->moveTo(gamemap, perso->parent->pos.x, perso->parent->pos.y-1);
                            perso->nextTick = 1000;
                            horloge.tick();
                            persoY--;
                        }
                    break;

                case sf::Keyboard::Down :
                    if(persoY < NB_BLOCS_L-5)
                        if(!gamemap->map[persoX][persoY+1]->cantWalk){
                            perso->moveTo(gamemap, perso->parent->pos.x, perso->parent->pos.y+1);
                            perso->nextTick = 1000;
                            horloge.tick();
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

        int dist = 10;

        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(persoX, persoY, 0, x, dist, gamemap);
        for(int x = 0; x < NB_BLOCS_L; x++)
            Fov(persoX, persoY, NB_BLOCS_H-1, x, dist, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(persoX, persoY, x, 0, dist, gamemap);
        for(int x = 0; x < NB_BLOCS_H; x++)
            Fov(persoX, persoY, x, NB_BLOCS_L-1, dist, gamemap);

        app.clear();


        aff.affiche(gamemap->getMap(std::max(persoX-DIST_FROM_LEFT-1, 0), std::max(persoY-DIST_FROM_UP-1, 0),  std::min(persoX+DIST_FROM_LEFT, NB_BLOCS_L), std::min(persoY+DIST_FROM_UP, NB_BLOCS_H)));

        app.display();

    }


    return EXIT_SUCCESS;
}

sf::Vector2i getPersoTitle(sf::Sprite sprite)
{
    return sf::Vector2i(sprite.getPosition().x/BLOCS_SIZE, sprite.getPosition().y/BLOCS_SIZE);
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
