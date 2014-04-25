#ifndef ENTITY_H_INCLUDE
#define ENTITY_H_INCLUDE

#include "Title.h"
#include <SFML/Graphics.hpp>

struct Title;

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void setPos(sf::Vector2i pos);
        sf::Vector2i getPos();
    protected:
        sf::Vector2i Pos;
        Title* parent;
    private:
};

#endif // ENTITY_H
