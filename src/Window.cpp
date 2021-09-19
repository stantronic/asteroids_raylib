

#include "Window.h"

Window::Window(float w, float h) : width(w), height(h) {
    InitWindow((int) width, (int) height, "Asteroids");
#ifdef USE_FULL_SCREEN
    SetWindowState(FLAG_FULLSCREEN_MODE);
#endif
    SetTargetFPS(60);
}

void Window::draw() {
    ClearBackground(BLACK);
}

Vector2 Window::performScreenWarp(Vector2 position) {
    if (position.x < 0)
        position.x += (float) width;
    if (position.x > width)
        position.x -= width;
    if (position.y < 0)
        position.y += height;
    if (position.y > height)
        position.y -= height;
    return position;
}

Vector2 Window::getCenter() {
    return Vector2{width * 0.5f, height * 0.5f};
}
