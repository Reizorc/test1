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

    sf::Sprite sprite;

    for(int x = 0; x < gamemap->x; x++)
    {
        for( int y = 0; y < gamemap->y; y++)
        {
            Title* title = gamemap->map[x][y];
            if(title->visible || title->discoverd)
            {
                if(title->discoverd && !title->visible)
                    sprite.setColor(sf::Color(255, 255, 255, 128));
                else
                    sprite.setColor(sf::Color(255, 255, 255, 255));

                sprite.setPosition(64*(x+1)-64, 64*(y+1)-64);
                sprite.setTexture(getTexture(title->spriteName));
                app->draw(sprite);
            }

        }
    }
//    app.draw(perso);
//    app.draw(spider);
}

int print::registerSprite(string vName, int id = 0)
{
    string name = vName.substr(0, vName.find_first_of("."));
    if(NameMap[name] == 0)
    {

        if(!id)
        {
            max_id += 10;
            id = max_id;
        }
        TextureMap[id];// = new sf::Texture();
        TextureMap[id].loadFromFile("res/img/" + vName);
        NameMap[name] = id;
        return id;
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
