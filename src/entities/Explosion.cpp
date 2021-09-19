//
// Created by Steven Stanton on 18/09/2021.
//

#include "Explosion.h"

Explosion::Explosion(Color color) : ringColor(color) {
    alive = false;
}

void Explosion::explode(Vector2 coords) {
    position = coords;
    alive = true;
}

void Explosion::update(Window *window) {
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

void Explosion::draw() {
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
