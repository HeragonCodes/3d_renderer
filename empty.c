#include "empty.h"

empty empty_init(void) {
    empty obj;
    obj.pos = (vector3){0.0f, 0.0f, 0.0f};
    obj.rot = (vector3){0.0f, 0.0f, 0.0f};
    obj.sca = (vector3){0.0f, 0.0f, 0.0f};
    return obj;
}

void translate(empty *obj, vector3 pos_change) {
    vec3_add(&obj->pos, pos_change);
}
void rotate(empty *obj, vector3 rot_change) {
    vec3_add(&obj->rot, rot_change);
}
void scale(empty *obj, vector3 sca_change) {
    vec3_add(&obj->sca, sca_change);
}