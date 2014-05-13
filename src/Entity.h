#ifndef ENTITY_H_INCLUDE
#define ENTITY_H_INCLUDE

#include "Title.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <iostream>

struct Title;
class Map;

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void tick();

        void setPos(sf::Vector2i pos);
        sf::Vector2i getPos();

        std::string getSprite();
        void setSprite(std::string sprite);

        Title* setParent(Title* newTitle);
        void moveTo(Map* gamemap, int x, int y);

        Title* parent;

        int nextTick;

    protected:
        sf::Vector2i Pos;

        std::string spriteName;
    private:
};

#endif // ENTITY_H
