#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Ca ne marche pas!! SHIT!!" << std::endl;
    }

    sf::RenderWindow app(sf::VideoMode(800, 600), "Dis moi si tu vois ca écrit ;)");

    sf::Sprite Logo;
    sf::Texture Tex_Logo;
    Tex_Logo.loadFromFile("RogueLike.png");
    Logo.setTexture(Tex_Logo);
    Logo.setPosition(250,290);

    sf::Text accueil;
    accueil.setString("Bienvenue dans:");
    accueil.setCharacterSize(35);
    accueil.setColor(sf::Color::Red);
    accueil.setStyle(sf::Text::Bold);
    accueil.setFont(font);
    accueil.setPosition(250,250);


    while (app.isOpen())
    {

        sf::Event event;
        while (app.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                app.close();
        }


        app.clear();

        //TOUS LES DRAW ICI!!!!
        app.draw(accueil);
        app.draw(Logo);

        app.display();
    }

    return EXIT_SUCCESS;
}
