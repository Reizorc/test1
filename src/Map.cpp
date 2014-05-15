#include "Map.h"
#include <assert.h>
#include "gametitle.h"

Map::Map(int maxH, int maxL)
{

    this->x = 0;
    this->y = 0;

    if(maxL && maxH)
    {
        for(int x = 0; x < maxH; x++)
        {
            vector<Title*> row;
            for(int y = 0; y < maxL; y++)
            {
                row.push_back(new Title);
                row[y]->ID = tilemap(y,x);
                row[y]->pos = sf::Vector2i(x, y);
                row[y]->visible = 0;
                row[y]->discoverd = 0;

                if(row[y]->ID == 1)
                {
                    row[y]->cantWalk = 1;
                    row[y]->opaque = 1;
                    row[y]->spriteName = "stone";
                }
                else
                {
                    row[y]->cantWalk = 0;
                    row[y]->opaque = 0;
                    row[y]->spriteName = "grass";
                }
            }
            map.push_back(row);
        }

        for(int x = 1; x < maxH-1; x++)
        {
            for(int y = 1; y < maxL-1; y++)
            {
                map[x][y]->voisin.top = map[x][y-1];
                map[x][y]->voisin.bottom = map[x][y+1];
                map[x][y]->voisin.left = map[x-1][y];
                map[x][y]->voisin.right = map[x+1][y];
            }
        }
    }

}

Map* Map::getMap(int x1, int y1, int x2, int y2)
{
    Map* mapToReturn;
    mapToReturn = new Map(0, 0);
    int y1start = y1;
    for(;x1 < x2; x1++)
    {
        vector<Title*> row;
        mapToReturn->y = 0;
        for(;y1 < y2; y1++)
        {
            row.push_back(this->map[x1][y1]);
            mapToReturn->y++;
        }
        y1 = y1start;
        mapToReturn->map.push_back(row);
        mapToReturn->x++;
    }
    return mapToReturn;
}

Map::~Map()
{

}
