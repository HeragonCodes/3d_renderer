#include "vector.h"
#include <math.h>

vector3 vec3_rotate_y(vector3 v, float angle) {
    vector3 rotated_v = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_v;
}

void vec3_add(vector3 *v, vector3 w) {
    v->x+=w.x;
    v->y+=w.y; 
    v->z+=w.z;
}