#include "types.h"

typedef struct collisionObject {
    PhysVector gravAccel;
    PhysVector netForce;
    Collider* collider;
}
