#include "print.h"
#include "define.h"

print::print(sf::RenderWindow &vapp)
{
    app = &vapp;
    max_id = 0;
    sprite.setScale((float)BLOCS_SIZE/64, (float)BLOCS_SIZE/64);
}

print::~print()
{
    //dtor
}

void print::affiche(Map* gamemap)
{
    for(int x = 0; x < gamemap->x; x++)
    {
        for( int y = 0; y < gamemap->y; y++)
        {
            Title* title = gamemap->map[x][y];
            if((title->visible || title->discoverd))
            {
                if(title->discoverd && !title->visible && !title->cantWalk)
                    sprite.setColor(sf::Color(255, 255, 255, 128));
                else
                    sprite.setColor(sf::Color(255, 255, 255, 255));

                sprite.setPosition(BLOCS_SIZE*(x+1)-BLOCS_SIZE, BLOCS_SIZE*(y+1)-BLOCS_SIZE);
                sprite.setTexture(getTexture(title->spriteName));
                app->draw(sprite);
                for(auto& Entity : title->entity)
                {
                    sprite.setTexture(getTexture(Entity->getSprite()));
                    app->draw(sprite);
                }
            }

        }
    }
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
