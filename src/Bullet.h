#ifndef LEARN_CMAKE_BULLET_H
#define LEARN_CMAKE_BULLET_H

#include <raymath.h>
#include <raylib.h>
#include "Utils.h"
#include "Constants.h"

class Bullet {
public:
    bool isAlive() const {
        return life > 0;
    }

    Rectangle getCollisionRec() {
        return collisionRecFromCenter(pos, 6);
    }

    //returns true when actually shoots
    bool shoot(Vector2 start, float angle, Vector2 base_velocity) {
        if (isAlive()) return false;
        life = BULLET_LIFE_SPAN;
        pos = start;
        velocity = Vector2Add(base_velocity, Vector2Rotate({0, -8}, angle));
        return true;
    }

    void update() {
        if (isAlive()) {
            pos = Vector2Add(pos, velocity);
            life -= 1;
        }
    }

    void draw() {
        if (isAlive()) {
            DrawCircle(
                    (int) pos.x,
                    (int) pos.y,
                    3.f,
                    YELLOW
            );
#ifdef SHOW_COLLISION_RECTS
            DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
#endif
        }
    }

private:
    int life{};
    Vector2 pos{};
    Vector2 velocity{};
};

#endif //LEARN_CMAKE_BULLET_H
