//
// Created by Steven Stanton on 15/09/2021.
//
#include "raylib.h"
#include "Utils.h"

Rectangle collisionRecFromCenter(Vector2 position, float size) {
    return Rectangle{
            position.x - size,
            position.y - size,
            size,
            size};
}

bool areColliding(Entity *a, Entity *b) {
    return (a->isAlive()
            && b->isAlive()
            && CheckCollisionRecs(a->getCollisionRec(), b->getCollisionRec())
    );
}
