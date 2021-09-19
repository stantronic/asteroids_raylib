#ifndef ASTEROIDS_ENTITY_H
#define ASTEROIDS_ENTITY_H

#include "raylib.h"
#include "raymath.h"
#include "../Window.h"

class Entity {
public:

    virtual ~Entity() = default;

    virtual void update(Window *window) = 0;

    virtual void draw() = 0;

    virtual bool isAlive() const { return alive; }

    Vector2 getPosition() const { return position; }

    void positionAt(Vector2 new_position);

    void moveBy(Vector2 vector);

    Rectangle getCollisionRec();

protected:
    Vector2 position{};
    float collisionRecSize = 0.f;
    bool alive{false};
};


#endif //ASTEROIDS_ENTITY_H
