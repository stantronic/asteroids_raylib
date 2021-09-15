#include "raylib.h"
#include "Constants.h"
#include "Window.h"
#include "SoundBoard.h"
#include "Utils.h"
#include "Bullet.h"

class Rocket {
public:
    Rocket(Window *window, SoundBoard *soundBoard) : sounds(soundBoard) {
        pos = {0.5f * (float) window->width, 0.5f * (float) window->height};
    }

    Vector2 pos{};

    void rotate(float amount) {
        rotation += amount;
    }

    bool isAlive() const {
        return !exploded;
    }

    bool fireHitsRock(Rectangle rockRec) {
        for (auto &bullet : bullets) {
            if(bullet.isAlive() && CheckCollisionRecs(bullet.getCollisionRec(), rockRec)){
                return true;
            }
        }
        return false;
    }

    void shoot() {
        if (shooterCoolDown == 0 && !exploded) {

            for (auto &bullet : bullets) {
                if (bullet.shoot(pos, rotation, velocity)) {
                    sounds->fire();
                    shooterCoolDown = 10;
                    break;
                }
            }
        }
    }

    void performThrust(bool boosting) {
        if (!isBoosting)
            sounds->thrust();
        isBoosting = boosting;
        Vector2 thrust = Vector2Scale({0, -1}, isBoosting ? 0.5 : 0);
        thrustVelocity = Vector2Rotate(thrust, rotation);
    }

    void explode() {
        if (exploded)
            return;
        exploded = true;
        sounds->boom();
        explosion.explode(pos);
    }

    Rectangle getCollisionRec() {
        return collisionRecFromCenter(pos, 10);
    }

    void update() {

        if (exploded) {
            explosion.update();
        } else {

            velocity = Vector2Add(velocity, thrustVelocity);
            if (Vector2Length(velocity) > 20) {
                velocity = Vector2Scale(Vector2Normalize(velocity), 20);
            }

            pos = Vector2Add(pos, velocity);

            for (auto &bullet : bullets) {
                bullet.update();
            }
            if (shooterCoolDown > 0) {
                shooterCoolDown--;
            }
        }
    }

    void draw() {
        for (auto &bullet : bullets) {
            bullet.draw();
        }
        if (exploded) {
            explosion.draw();
            DrawText("You Lose", 100, 100, 40, WHITE);
        } else {

            Vector2 nose = Vector2Add(pos, Vector2Rotate(noseRelative, rotation));
            Vector2 leftWing = Vector2Add(pos, Vector2Rotate(leftWingRelative, rotation));
            Vector2 rightWing = Vector2Add(pos, Vector2Rotate(rightWingRelative, rotation));
            DrawTriangle(nose, leftWing, rightWing, isBoosting ? ORANGE : RED);
            if (SHOW_COLLISION_RECTS) {
                DrawRectangleLinesEx(getCollisionRec(), 1, WHITE);
            }
        }
    }

private:
    SoundBoard *sounds;
    int shooterCoolDown{};
    float rotation{};
    bool exploded{};
    Vector2 velocity{};
    Vector2 thrustVelocity{};

    bool isBoosting{};
    Bullet bullets[MAX_BULLETS]{};
    Explosion explosion{RED};
    Vector2 noseRelative{0, -20};
    Vector2 leftWingRelative{-15, 20};
    Vector2 rightWingRelative{15, 20};
};