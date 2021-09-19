//
// Created by Steven Stanton on 18/09/2021.
//
#include "Bullet.h"
#include "raylib.h"
#include "raymath.h"

void Bullet::shoot(Vector2 start, Vector2 base_velocity, float angle) {
    alive = true;
    life = BULLET_LIFE_SPAN;
    position = start;
    velocity = Vector2Add(base_velocity, Vector2Rotate({0, -8}, angle));
}

void Bullet::update(Window *window) {
    if (alive) {
        moveBy(velocity);
        life -= 1;
        if (life <= 0) alive = false;
    }
}

void Bullet::draw() {
    if (alive) {
        DrawCircle(
                (int) position.x,
                (int) position.y,
                3.f,
                YELLOW
        );
#ifdef SHOW_COLLISION_RECTS
        DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
#endif
    }
}

void Bullet::kill() {
    life = 0;
    alive = false;
}


