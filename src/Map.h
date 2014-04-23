#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdlib.h>
#include "Title.h"

using namespace std;

class Map
{
    public:
        Map(int maxH, int maxL);
        Map* getMap(int x1, int y1, int x2, int y2);
        virtual ~Map();
        vector< vector<Title*> > map;
        int x;
        int y;
    protected:
    private:
};

#endif // MAP_H
