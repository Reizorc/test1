#include "Map.h"
#include <assert.h>

Map::Map(int maxH, int maxL)
{
    int* gametitle[12][9]=
    {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    for(int x = 0; x < maxH; x++)
    {
        vector<Title*> row;
        for(int y = 0; y < maxL; y++)
        {
            row.push_back(new Title);
            row[y]->ID = gametitle[x][y]; //rand() % 2 + 0; // rand() % max + min
            row[y]->pos = sf::Vector2i(x, y);
            row[y]->visible = 0;
            if(row[y]->ID == 1)
            {
                row[y]->cantWalk = 1;
                row[y]->opaque = 1;
            }
            else
            {
                row[y]->cantWalk = 0;
                row[y]->opaque = 0;
            }
        }
        map.push_back(row);
    }
    map[0][0]->opaque = 0;
    assert(1==0);
}

Map::~Map()
{

}
