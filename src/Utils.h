#ifndef UTILS
#define UTILS
#include "raylib.h"

Rectangle collisionRecFromCenter(Vector2 position, float size)
{
    return Rectangle{
        position.x - size,
        position.y - size,
        size * 2.f,
        size * 2.f};
}
#endif