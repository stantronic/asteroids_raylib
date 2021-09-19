//
// Created by Steven Stanton on 05/09/2021.
//

#ifndef LEARN_CMAKE_EXPLOSION_H
#define LEARN_CMAKE_EXPLOSION_H

#include "raylib.h"
#include "Entity.h"


class Explosion : public Entity {
public:
    explicit Explosion(Color color);

    void explode(Vector2 coords);

    void update(Window *window) override;

    void draw() override;

private:
    int size = 5;
    float alpha = 1.f;
    float ringThickness = 10.f;
    Color ringColor;
};

#endif //LEARN_CMAKE_EXPLOSION_H
