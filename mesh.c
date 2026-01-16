#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "vector.h"

mesh load_model(const char *filename) {

    mesh m = {0};

    FILE *file = fopen(filename, "r");
    if (!file) {
        return m;
    }

    m.vertices = malloc(sizeof(vector3) * 1000);
    m.faces = malloc(sizeof(face) * 1000);

    char buffer[128]; 

    while (fscanf(file, "%s", buffer) != EOF) {
        if (buffer[0] == 'v' && buffer[1] == '\0') {
            fscanf(file, "%f %f %f", 
                &m.vertices[m.v_count].x, 
                &m.vertices[m.v_count].y, 
                &m.vertices[m.v_count].z);
            m.v_count++;
        }
        else if (buffer[0] == 'f' && buffer[1] == '\0') {
            int v[4], vt[4], vn[4];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                    &v[0], &vt[0], &vn[0],   
                    &v[1], &vt[1], &vn[1],   
                    &v[2], &vt[2], &vn[2],  
                    &v[3], &vt[3], &vn[3]);
            if (matches == 12) {
                m.faces[m.f_count].a = v[0] - 1; 
                m.faces[m.f_count].b = v[1] - 1;
                m.faces[m.f_count].c = v[2] - 1;
                m.f_count++;
                m.faces[m.f_count].a = v[0] - 1;
                m.faces[m.f_count].b = v[2] - 1;
                m.faces[m.f_count].c = v[3] - 1;
                m.f_count++;
            }
            else if (matches == 9) {
            m.faces[m.f_count].a = v[0] - 1; 
            m.faces[m.f_count].b = v[1] - 1;
            m.faces[m.f_count].c = v[2] - 1;
            m.f_count++;
            }
        }
    }

    fclose(file);
    return m;
}