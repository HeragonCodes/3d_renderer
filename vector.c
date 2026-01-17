#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include <math.h>

void vec3_add(vector3 *v, vector3 w) {
    v->x+=w.x;
    v->y+=w.y; 
    v->z+=w.z;
}

void vec2_add(vector2 *v, vector2 w) {
    v->x+=w.x;
    v->y+=w.y; 
}

void vec3_scale(vector3 *v, float scalar) {
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

void vec2_scale(vector2 *v, float scalar) {
    v->x *= scalar;
    v->y *= scalar;
}

float vec3_dprod(vector3 v, vector3 w) {
    return v.x*w.x+v.y*w.y+v.z*w.z;
}

float vec2_dprod(vector2 v, vector2 w) {
    return v.x*w.x+v.y*w.y;
}

matrix matrix_init(int m, int n, float v[]) {
    matrix H;
    H.m = m;
    H.n = n;
    H.values = malloc(m * sizeof(float *));

    for (int i = 0; i < m; i++)
    {
        H.values[i] = malloc(n * sizeof(float));
        for (int j = 0; j < n; j++)
        {
            H.values[i][j] = v[i*n+j];
        }
        
    }
    return H;
    
}

void free_matrix(matrix H) {
    for (int i = 0; i < H.m; i++) {
        free(H.values[i]);
    }
    free(H.values);
}

void vec3_matrixmul(vector3 *v, matrix H) {
    if (H.n != 3) {printf("ERROR! Matrix width different from vector size\n"); return;}
    if (H.m != 3) {printf("ERROR! Matrix height different from vector size\n"); return;}

    float x = H.values[0][0]*v->x + H.values[0][1]*v->y + H.values[0][2]*v->z;
    float y = H.values[1][0]*v->x + H.values[1][1]*v->y + H.values[1][2]*v->z;
    float z = H.values[2][0]*v->x + H.values[2][1]*v->y + H.values[2][2]*v->z;

    v->x = x;
    v->y = y;
    v->z = z;
}

void vec2_matrixmul(vector2 *v, matrix H) {
    if (H.n != 2) {printf("ERROR! Matrix width different from vector size\n"); return;}
    if (H.m != 2) {printf("ERROR! Matrix height different from vector size\n"); return;}

    float x = H.values[0][0]*v->x + H.values[0][1]*v->y;
    float y = H.values[1][0]*v->x + H.values[1][1]*v->y;

    v->x = x;
    v->y = y;
}