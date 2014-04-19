#include <SFML/Graphics.hpp>
#include <iostream>

void print(sf::RenderWindow& app, int gamemap[16][16], int xsize, int ysize);

int main()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Ca ne marche pas!! SHIT!!" << std::endl;
    }

    sf::RenderWindow app(sf::VideoMode(800, 600), "Dis moi si tu vois ca écrit ;)");

    int gamemap[16][16];
    for(int x = 0; x < 16; x++)
        for(int y = 0; y < 16; y++)
            gamemap[x][y] = 0;


    sf::Sprite Logo;
    sf::Texture Tex_Logo;
    Tex_Logo.loadFromFile("RogueLike.png");
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
        print(app, gamemap, 16, 16);
        app.display();
        }


    return EXIT_SUCCESS;
}

void print(sf::RenderWindow& app, int gamemap[16][16], int xsize, int ysize)
{
    sf::Text text;
    text.setCharacterSize(30);
    text.setColor(sf::Color::White);
    for(int x = 0; x < xsize; x++)
    {
        for(int y = 0; y < ysize; y++)
        {
            if(gamemap[x][y] == 0)
            if(gamemap[x][y] != 0)
                text.setPosition(30*(x+1), 30*(y+1));
                text.setString("#");
                app.draw(text);
        }
    }
}
