#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
#ifndef WINDOW
#define WINDOW
#include "raylib.h"

class Window
{
public:
    const int width;
    const int height;
    Window(int w, int h) : width(w), height(h)
    {
        InitWindow(width, height, "Asteroids");
        SetTargetFPS(60);
    }

    void draw()
    {
        ClearBackground(BLACK);
    }

    Vector2 performScreenWarp(Vector2 position)
    {
        if (position.x < 0)
            position.x += width;
        if (position.x > width)
            position.x -= width;
        if (position.y < 0)
            position.y += height;
        if (position.y > height)
            position.y -= height;
        return position;
    }

    void tearDown(){
        CloseWindow();
    }
};

#endif
#pragma clang diagnostic pop