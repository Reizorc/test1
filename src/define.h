#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define BLOCS_SIZE 32

#define NB_BLOCS_L 100
#define NB_BLOCS_H 100

#define NB_BLOCS_X 11*(float)((float)64/BLOCS_SIZE)
#define NB_BLOCS_Y 9*(float)((float)64/BLOCS_SIZE)

#define DIST_FROM_UP (int)((float)(NB_BLOCS_Y-1)/2)+1
#define DIST_FROM_LEFT (int)((float)(NB_BLOCS_X-1)/2)+1

//jai ajouter une coupe de (float) pour etre sur

#endif // DEFINE_H_INCLUDED
