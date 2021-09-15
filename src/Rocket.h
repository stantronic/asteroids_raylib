#include "raylib.h"
#include "Constants.h"
#include "Window.h"
#include "SoundBoard.h"
#include "Utils.h"
#include "Bullet.h"
#include "Event.h"
#include "Movable.h"
#include "Explosion.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCSimplifyInspection"

#ifndef ROCKET_H
#define ROCKET_H

class Rocket : public Movable {
public:
    explicit Rocket(Window *window, EventBus *eventBus) : events(eventBus) {
        position = {0.5f * (float) window->width, 0.5f * (float) window->height};
        collisionRecSize = 20;
        alive = true;
    }

    void rotate(float amount) {
        rotation += amount;
    }


    bool fireHitsRock(Rectangle rockRec) {
        if (!isAlive()) return false;
        for (auto &bullet : bullets) {
            if (bullet.isAlive() && CheckCollisionRecs(bullet.getCollisionRec(), rockRec)) {
                return true;
            }
        }
        return false;
    }

    void shoot() {
        if (shooterCoolDown == 0 && alive) {

            for (auto &bullet : bullets) {
                if (bullet.shoot(position, rotation, velocity)) {
                    events->shoot();
                    shooterCoolDown = 10;
                    break;
                }
            }
        }
    }

    void performThrust(bool boosting) {
        if (!isBoosting && boosting) {
            events->thrust();
        }
        isBoosting = boosting;
        Vector2 thrust = Vector2Scale({0, -1}, isBoosting ? 0.5 : 0);
        thrustVelocity = Vector2Rotate(thrust, rotation);
    }

    void explode() {
        if (!alive) return;
        alive = false;
    }

    void update(Window *window) override {
        for (auto &bullet : bullets) {
            bullet.update();
        }
        if (isAlive()) {
            if (IsKeyDown(KEY_L)) {
                rotate(10);
            }
            if (IsKeyDown(KEY_J)) {
                rotate(-10);
            }
            if (IsKeyDown(KEY_S)) {
                shoot();
            }
            performThrust(IsKeyDown(KEY_A));

            position = window->performScreenWarp(position);
            velocity = Vector2Add(velocity, thrustVelocity);

            if (Vector2Length(velocity) > 20) {
                velocity = Vector2Scale(Vector2Normalize(velocity), 20);
            }

            moveBy(velocity);

            if (shooterCoolDown > 0) {
                shooterCoolDown--;
            }
        }
    }

    void draw() override {
        for (auto &bullet : bullets) {
            bullet.draw();
        }
        if (alive) {
            Vector2 nose = Vector2Add(position, Vector2Rotate(noseRelative, rotation));
            Vector2 leftWing = Vector2Add(position, Vector2Rotate(leftWingRelative, rotation));
            Vector2 rightWing = Vector2Add(position, Vector2Rotate(rightWingRelative, rotation));
            DrawTriangle(nose, leftWing, rightWing, isBoosting ? ORANGE : RED);
#ifdef SHOW_COLLISION_RECTS
            DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
#endif
        }
    }

    void revive() {
        alive = true;
    }

private:
    EventBus *events;
    int shooterCoolDown{};
    float rotation{};
    Vector2 velocity{};
    Vector2 thrustVelocity{};

    bool isBoosting{};
    Bullet bullets[MAX_BULLETS]{};
    Vector2 noseRelative{0, -20};
    Vector2 leftWingRelative{-15, 20};
    Vector2 rightWingRelative{15, 20};
};

#endif
#pragma clang diagnostic pop