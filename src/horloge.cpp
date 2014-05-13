#include "horloge.h"

Horloge::Horloge()
{

}

void Horloge::add(Entity* entity)
{
    entitys.push_back(entity);
}

int Horloge::tick()
{
    for(Entity* entity : entitys)
    {
       entity->nextTick = entity->nextTick - minimumTick;
       if(entity->nextTick == 0)
            entity->tick();
    }

    int tick = 0;

    for(Entity* entity : entitys)
    {


        if(tick == 0)
            tick = entity->nextTick;
        else if(entity->nextTick < tick && entity->nextTick > 0)
        {
            tick = entity->nextTick;
        }
        std::cout << entity->nextTick << std::endl;
    }

    minimumTick = tick;

    return minimumTick;
}

int Horloge::tick(Entity* entity)
{
    while(!(entity->nextTick == 0))
        tick();
}
