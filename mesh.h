#ifndef MESH_H
#define MESH_H
#include "vector.h"

typedef struct face
{
    int a, b, c;
} face;

typedef struct mesh
{
    vector3 *vertices;
    face *faces;
    int v_count;
    int f_count;
} mesh;

mesh load_model(const char *filename);

#endif