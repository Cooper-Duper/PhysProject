//Need the custom vector types
#include "../structs/types.h"

//Adds two physics vectors and returns the sum
PhysVec add(PhysVec a, PhysVec b) {
    PhysVec out;
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;

    return out;
}

//Subtracts two physics vectors and returns the value
PhysVec subtract(PhysVec a, PhysVec b) {
    PhysVec out;
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;

    return out;
}

