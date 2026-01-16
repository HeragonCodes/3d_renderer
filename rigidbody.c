#include "rigidbody.h"

rigidbody rigidbody_init(empty obj) {
    rigidbody rb;

    rb.speed = (vector3){0.0f, 0.0f, 0.0f};
    rb.acceleration = (vector3){0.0f, 0.0f, 0.0f};
    rb.mass = 1.0f;
    rb.gravity = 9.80665f;
    rb.air_drag = 1.0f;
    
    return rb;
}