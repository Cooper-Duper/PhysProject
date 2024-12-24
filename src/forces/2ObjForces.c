//Do not need to include "types" directly since "objects" includes it... Don't know that I like this
#include "../structs/objects.h"

void getFriction(PhysObj obj1, PhysObj obj2) {
    float totalCoeff = obj1.coeffFriction + obj2.coeffFriction;
}
