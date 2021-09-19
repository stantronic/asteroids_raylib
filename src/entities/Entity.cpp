#include "Entity.h"
#include "../Utils.h"

void Entity::positionAt(Vector2 new_position) {
    position = new_position;
}

void Entity::moveBy(Vector2 vector) {
    position = Vector2Add(position, vector);
}

Rectangle Entity::getCollisionRec() {
    return collisionRecFromCenter(position, collisionRecSize);
}
