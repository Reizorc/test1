#include "print.h"

print::print(sf::RenderWindow &vapp)
{
    app = &vapp;
    max_id = 0;
}

print::~print()
{
    //dtor
}

void print::affiche(Map* gamemap)
{
    sf::Sprite grass;
    sf::Sprite stone;

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
                    app->draw(grass);
                }
                if(title->ID == 1)
                {
                    stone.setPosition(64*(x+1)-64, 64*(y+1)-64);
                    app->draw(stone);
                }
            }

        }
    }
//    app.draw(perso);
//    app.draw(spider);
}

int print::registerSprite(string name)
{
    if(NameMap[name] == 0)
    {
        max_id += 10;
        TextureMap[max_id];// = new sf::Texture();
        TextureMap[max_id].loadFromFile("res/img/" + name);
        NameMap[name] = max_id;
        std::cout << max_id << std::endl;
        return max_id;
    }
    else
    {
        std::cout << NameMap[name] << std::endl;
        return NameMap[name];
    }

}

const sf::Texture& print::getTexture(int id)
{
    return TextureMap[id];
}

const sf::Texture& print::getTexture(string name)
{
    return TextureMap[NameMap[name]];
}
