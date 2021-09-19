#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
#ifndef WINDOW
#define WINDOW

#include "raylib.h"

class Window {
public:
    const float width;
    const float height;

    Window(float w, float h);

    void draw();

    Vector2 performScreenWarp(Vector2 position);

    ~Window() {
        CloseWindow();
    }

    Vector2 getCenter();
};

#endif
#pragma clang diagnostic pop