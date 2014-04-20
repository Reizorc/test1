#include <SFML/Graphics.hpp>
#include <iostream>

#define NB_BLOCS_L 8
#define NB_BLOCS_H 11


void affiche(sf::RenderWindow& app, char* gamemap[NB_BLOCS_H][NB_BLOCS_L]);

    sf::Font font;
    sf::Sprite perso;
    sf::Texture tex_perso;


int main()
{


    sf::RenderWindow app(sf::VideoMode(800, 600), "TILE MAP!!)");

    font.loadFromFile("arial.ttf");

    tex_perso.loadFromFile("res/img/perso.png");
    perso.setTexture(tex_perso);
    perso.setPosition(0,0);



    char* gamemap[NB_BLOCS_H][NB_BLOCS_L] =
    {
    {'1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','1'},
    {'1','1','0','1','1','1','1','1'}
    };


    while (app.isOpen())
    {

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
                        perso.move(-64,0);

                        break;

                    case sf::Keyboard::Right :
                        perso.move(64,0);
                        break;

                    case sf::Keyboard::Up :
                        perso.move(0,-64);
                        break;

                    case sf::Keyboard::Down :
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


        app.clear();
        affiche(app, gamemap);

        app.display();

        }


    return EXIT_SUCCESS;
}

void affiche(sf::RenderWindow &app, char* gamemap[NB_BLOCS_H][NB_BLOCS_L])
{



    sf::Sprite grass;
    sf::Texture tex_grass;
    tex_grass.loadFromFile("res/img/grass.png");
    grass.setTexture(tex_grass);

    sf::Sprite stone;
    sf::Texture tex_stone;
    tex_stone.loadFromFile("res/img/stone.png");
    stone.setTexture(tex_stone);

    for(int x = 0; x < NB_BLOCS_H; x++)
    {
        for( int y = 0; y < NB_BLOCS_L; y++)
        {
            if(gamemap[x][y] == '0')
            {
                grass.setPosition(64*(x+1), 64*(y+1));
                app.draw(grass);
            }
            if(gamemap[x][y] == '1')
            {
                stone.setPosition(64*(x+1), 64*(y+1));
                app.draw(stone);
            }


        }
    }
    app.draw(perso);
}


