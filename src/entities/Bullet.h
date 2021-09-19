#ifndef LEARN_CMAKE_BULLET_H
#define LEARN_CMAKE_BULLET_H

#include <raymath.h>
#include <raylib.h>
#include "../Utils.h"
#include "Entity.h"
#include "../Constants.h"

class Bullet : public Entity {
public:

    Bullet() : life(0), velocity({0, 0}) {
        collisionRecSize = 6;
    }

    //returns true when actually shoots
    void shoot(Vector2 start, Vector2 base_velocity, float angle);

    void update(Window *window) override;

    void draw() override;

    void kill();

    Vector2 getVelocity() const { return velocity; }

private:
    int life;
    Vector2 velocity;
};

#endif //LEARN_CMAKE_BULLET_H
