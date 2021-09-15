//
// Created by Steven Stanton on 05/09/2021.
//

#ifndef LEARN_CMAKE_BULLET_H
#define LEARN_CMAKE_BULLET_H

#include <raymath.h>
#include <raylib.h>
#include "Utils.h"
#include "Constants.h"

class Bullet
{
public:
    bool isAlive() const
    {
        return life > 0;
    }

    Rectangle getCollisionRec()
    {
        return collisionRecFromCenter(pos, 4);
    }

    //returns true when actually shoots
    bool shoot(Vector2 start, float angle, Vector2 base_velocity)
    {
        if (isAlive())
            return false;

        life = 60;
        pos = start;
        velocity = Vector2Add(base_velocity, Vector2Rotate({0, -8}, angle));
        return true;
    }
    void update()
    {
        if (isAlive())
        {
            pos = Vector2Add(pos, velocity);
            life -= 1;
        }
    }
    void draw()
    {
        if (isAlive())
        {
//            printf("drawing bullet %f", pos.x);
            DrawCircle(pos.x, pos.y, 3, YELLOW);
            if (SHOW_COLLISION_RECTS)
            {
                DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
            }
        }
    }

private:
    int life{};
    Vector2 pos{};
    Vector2 velocity{};
};

#endif //LEARN_CMAKE_BULLET_H
