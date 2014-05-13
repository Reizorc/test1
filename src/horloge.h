#ifndef HORLOGE_H
#define HORLOGE_H

#include <Entity.h>

class Horloge
{
    public:
        Horloge();
        void add(Entity* entity);
        int tick();
        int tick(Entity* entity);
    protected:
        std::vector< Entity* > entitys;
        int minimumTick;
    private:
};

#endif // HORLOGE_H
