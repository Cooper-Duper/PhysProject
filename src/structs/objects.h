#include "types.h"

typedef struct Obj {
    float mass;
    float coeffFriction;
    PhysVec gravAccel;
    PhysVec netForce;
    //Collider* collider;
} PhysObj;
