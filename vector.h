#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector3
{
    float x, y, z;
} vector3;

typedef struct vector2
{
    float x, y;
} vector2;

typedef struct matrix
{
    int m, n;
    float **values; 
} matrix;


void vec3_add(vector3 *v, vector3 w);
void vec2_add(vector2 *v, vector2 w);
void vec3_scale(vector3 *v, float scalar);
void vec2_scale(vector2 *v, float scalar);
matrix matrix_init(int m, int n, float v[]);
void vec3_matrixmul(vector3 *v, matrix H);
void vec2_matrixmul(vector2 *v, matrix H);
void free_matrix(matrix H);


#endif