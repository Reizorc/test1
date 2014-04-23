#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include <SFML/Graphics.hpp>

struct Title
{
    sf::Vector2i pos;
    sf::Vector2i realPos;
    int cantWalk;
    int ID;
    int visible;
    int opaque;
};

#endif // TITLE_H_INCLUDED
