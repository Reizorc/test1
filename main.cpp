#include <SFML/Graphics.hpp>
#include <iostream>

#define NB_BLOCS_L 4
#define NB_BLOCS_H 4


void affiche(sf::RenderWindow& app, char** map);

int main()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Ca ne marche pas!! SHIT!!" << std::endl;
    }

    sf::RenderWindow app(sf::VideoMode(800, 600), "Dis moi si tu vois ca écrit ;)");

    char* map[] =
    {
    "0,1,0,1",
    "1,0,0,1",
    "0,1,1,0",
    "0,1,1,0",
    };

    sf::Sprite Logo;
    sf::Texture Tex_Logo;
    Tex_Logo.loadFromFile("res/img/RogueLike.png");
    Logo.setTexture(Tex_Logo);
    Logo.setPosition(250,285);

    sf::Text accueil;
    accueil.setString("Bienvenue dans");
    accueil.setCharacterSize(35);
    accueil.setColor(sf::Color::Red);
    accueil.setStyle(sf::Text::Bold);
    accueil.setFont(font);
    accueil.setPosition(265,250);


    while (app.isOpen())
    {

        sf::Event event;
        while (app.pollEvent(event))
        {

            if (event.type == sf::Event::Closed){
                app.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    app.close();
                }
        }


        app.clear();


        app.draw(accueil);
        app.draw(Logo);
        affiche(app, map);

        app.display();
        }


    return EXIT_SUCCESS;
}

void affiche(sf::RenderWindow &app, char** map)
{
    sf::Text text;
    text.setCharacterSize(30);
    text.setColor(sf::Color::White);
    for(int x = 0; x < NB_BLOCS_L; x++)
    {
        for( int y = 0; y < NB_BLOCS_H; y++)
        {
            if(map[x][y] == 0){
                std::cout << "map=0" << std::endl;
            }
            else if(map[x][y] != 0){
                std::cout << "map!=0" << std::endl;
                text.setPosition(30*(x+1), 30*(y+1));
                text.setString("#");
                app.draw(text);
                app.display();
        }
    }

}
}


