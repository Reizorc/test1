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
        virtual ~Map();
        vector< vector<Title*> > map;
    protected:
    private:
};

#endif // MAP_H
