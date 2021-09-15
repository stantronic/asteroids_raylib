//
// Created by Steven Stanton on 05/09/2021.
//

#ifndef LEARN_CMAKE_EXPLOSION_H
#define LEARN_CMAKE_EXPLOSION_H

#include "raylib.h"
#include "Movable.h"


class Explosion : public Movable {
public:
    explicit Explosion(Color color) : ringColor(color) {
        alive = false;
    }

    int size = 5;
    float ringThickness = 10.f;
    float alpha = 1.f;

    void explode(Vector2 coords) {
        position = coords;
        alive = true;
    }

    void update(Window *window) override {
        if (alive) {
            alpha *= 0.9;
            size += 5;
            if (size > 400)
                alive = false;
            ringThickness -= 0.2;
            if (ringThickness <= 0) {
                ringThickness = 0;
            }
        }
    }

    void draw() override {
        if (!alive) return;
        DrawRing(
                position,
                (float) size,
                (float) size + ringThickness,
                0,
                360,
                36,
                ColorAlpha(ringColor, alpha)
        );
    }

private:
    Color ringColor;
};

#endif //LEARN_CMAKE_EXPLOSION_H
