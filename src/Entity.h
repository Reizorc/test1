#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
    public:
        Entity();
        virtual ~Entity();

        void setPos(sf::Vector2i pos);
        sf::Vector2i getPos();
    protected:
        sf::Vector2i Pos;
    private:
};

#endif // ENTITY_H
