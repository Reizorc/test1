#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Entity;

struct Title
{
    sf::Vector2i pos;
    sf::Vector2i realPos;
    int cantWalk;
    int ID;
    int visible;
    int opaque;
    int player;
    std::vector< Entity > entity;
};

#endif // TITLE_H_INCLUDED
