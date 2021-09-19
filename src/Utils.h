#ifndef UTILS
#define UTILS

#include "raylib.h"
#include "entities/Entity.h"

Rectangle collisionRecFromCenter(Vector2 position, float size);

bool areColliding(Entity *a, Entity *b);

#endif