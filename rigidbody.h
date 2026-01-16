#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "empty.h"

typedef struct rigidbody
{
    empty obj;
    vector3 speed, acceleration;
    float mass, gravity, air_drag;
} rigidbody;

rigidbody rigidbody_init(empty obj);

#endif