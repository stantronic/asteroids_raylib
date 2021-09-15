#ifndef UTILS
#define UTILS

#include "raylib.h"
#include "Movable.h"

Rectangle collisionRecFromCenter(Vector2 position, float size);

bool areColliding(Movable *a, Movable *b);

#endif