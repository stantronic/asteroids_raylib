#include "SoundBoard.h"
#include "Event.h"
#include "Movable.h"

#ifndef ROCK_H
#define ROCK_H

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCSimplifyInspection"

class Rock : public Movable {

public:
    Rock(
            Vector2 pos,
            Vector2 vel,
            EventBus *events,
            float spin,
            int size) : Movable(),
                        velocity(vel),
                        events(events),
                        spin(spin),
                        rotation(spin),
                        size(size) {
        position = pos;
        alive = true;
        collisionRecSize = (float) size * 1.4f;
    }

    Rock(Rock &other) : Rock(other.position, other.velocity, other.events, other.spin, other.size) {
        alive = other.alive;
        printf("Rock copied!");
    }

    void explode() {
        alive = false;
    }

    void update(Window *window) override {
        position = window->performScreenWarp(position);

        if (alive) {
            rotation += spin;
            moveBy(velocity);
        } else {
            explosion.update(window);
        }
    }

    void draw() override {
        if (alive) {
            DrawPoly(position, 7, (float) size, rotation, BLUE);
#ifdef SHOW_COLLISION_RECTS
            DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
#endif
        } else {
            explosion.draw();
        }
    }

    static Rock *make(Vector2 position, Vector2 velocity, EventBus *events) {
        return new Rock{
                position,
                velocity,
                events,
                3,
                60,
        };
    }

private:
    Vector2 velocity{};
    EventBus *events;
    float spin{};
    float rotation{};
    int size{};
    Explosion explosion{BLUE};
};

#pragma clang diagnostic pop
#endif
