#include "Entity.h"
#include "outils.cpp"

Entity::Entity()
{
    parent = nullptr;
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

std::string Entity::getSprite()
{
    return spriteName;
}

void Entity::setSprite(std::string sprite)
{
    spriteName = sprite;
}

Title* Entity::setParent(Title* newTitle)
{
    Title* oldTitle = parent;
    if(parent)
    {
        std::vector<Entity*>* entity = &oldTitle->entity;
        entity->erase(std::remove(entity->begin(),entity->end(), this), entity->end());
    }
        newTitle->entity.push_back(this);
        parent = newTitle;
        return oldTitle;
}

void Entity::moveTo(Map* gamemap, int x, int y)
{
    setParent(gamemap->map[x][y]);
}
