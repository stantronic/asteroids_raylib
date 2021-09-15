//
// Created by Steven Stanton on 05/09/2021.
//

#ifndef LEARN_CMAKE_EXPLOSION_H
#define LEARN_CMAKE_EXPLOSION_H
#include "raylib.h"


class Explosion
{
public:
    Explosion(Color color) : ringColor(color)
    {
    }
    int size = 5;
    float ringThickness = 10.f;
    float alpha = 1.f;
    Vector2 position{};
    bool activated{};
    void explode(Vector2 coords)
    {
        position = coords;
        activated = true;
    }
    void update()
    {
        if (activated)
        {
            alpha *= 0.9;
            size += 5;
            if (size > 400)
                activated = false;
            ringThickness -= 0.2;
            if (ringThickness <= 0)
            {
                ringThickness = 0;
            }
        }
    }
    void draw()
    {
        if (activated)
        {
            DrawRing(position, size, size + ringThickness, 0, 360, 36, ColorAlpha(ringColor, alpha));
        }
    }

private:
    Color ringColor;
};

#endif //LEARN_CMAKE_EXPLOSION_H
