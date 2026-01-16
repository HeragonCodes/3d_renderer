#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector3
{
    float x, y, z;
} vector3;

vector3 vec3_rotate_y(vector3 v, float angle);
void vec3_add(vector3 *v, vector3 w);

#endif