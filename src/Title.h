#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

class Entity;
struct Title;

struct Voisin
{
    Title* left = nullptr;
    Title* right = nullptr;
    Title* top = nullptr;
    Title* bottom = nullptr;
};

struct Title
{
    sf::Vector2i pos;
    sf::Vector2i realPos;
    int cantWalk;
    int ID;
    int visible;
    int opaque;
    int player;
    int discoverd;
    Voisin voisin;
    std::string spriteName;
    std::vector< Entity* > entity;
};



#endif // TITLE_H_INCLUDED
