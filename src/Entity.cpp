#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{

}

sf::Vector2i Entity::getPos()
{
    return Pos;
}

void Entity::setPos(sf::Vector2i pos)
{
    Pos = pos;
}

void Entity::draw(sf::RenderWindow& app)
{
   // app.draw(getSpriteByID(this->getSpriteId()));
}
