#ifndef EMPTY_H
#define EMPTY_H
#include "vector.h"

typedef struct empty
{
    vector3 pos, rot, sca;
} empty;

empty empty_init(void);
void translate(empty *obj, vector3 pos_change); 
void rotate(empty *obj, vector3 rot_change);
void scale(empty *obj, vector3 sca_change);


#endif