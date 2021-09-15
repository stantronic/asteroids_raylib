#include "Movable.h"
#include "Utils.h"

void Movable::positionAt(Vector2 new_position) {
    position = new_position;
}

void Movable::moveBy(Vector2 vector) {
    position = Vector2Add(position, vector);
}

Rectangle Movable::getCollisionRec() {
    return collisionRecFromCenter(position, collisionRecSize);
}
