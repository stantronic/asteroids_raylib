#include "raylib.h"
#include <string>
#include "Constants.h"
#include "Window.h"
#include "Explosion.h"
#include "Rocket.h"
#include "SoundBoard.h"
#include "Asteroid.h"
#include <vector>

Asteroid *makeAsteroid(Vector2 position, Vector2 velocity, SoundBoard *soundBoard) {
    return new Asteroid{
            position,
            velocity,
            soundBoard,
            3,
            60,
    };
}


int main() {

    auto *window = new Window(1024, 1024);
    auto *soundBoard = new SoundBoard;


    auto *rocket = new Rocket(window, soundBoard);

    std::vector<Asteroid *> rocks;
    rocks.reserve(3);

    rocks.emplace_back(makeAsteroid({100, 100}, {5, 2}, soundBoard));
    rocks.emplace_back(makeAsteroid({200, 200}, {4, 9}, soundBoard));
    rocks.emplace_back(makeAsteroid({500, 800}, {-5, -2}, soundBoard));

    while (!WindowShouldClose()) {
        soundBoard->updateMusic();
        BeginDrawing();

        if (rocket->isAlive()) {
            if (IsKeyDown(KEY_L)) {
                rocket->rotate(10);
            }
            if (IsKeyDown(KEY_J)) {
                rocket->rotate(-10);
            }
            if (IsKeyDown(KEY_S)) {
                rocket->shoot();
            }

            rocket->performThrust(IsKeyDown(KEY_A));
            rocket->pos = window->performScreenWarp(rocket->pos);
            for (auto &rock : rocks) {
                rock->pos = window->performScreenWarp(rock->pos);
            }
        }
        rocket->update();
        for (auto &rock : rocks) {
            rock->update();
            Rectangle rockRec = rock->getCollisionRec();
            if (rocket->fireHitsRock(rockRec)) {
                rock->explode();
            }
            if (
                    rock->isAlive() &&
                    CheckCollisionRecs(
                            rock->getCollisionRec(),
                            rocket->getCollisionRec())) {
                rocket->explode();
            }
        }

        window->draw();
        for (auto &rock : rocks) {
            rock->draw();
        }
        rocket->draw();

        EndDrawing();
    }
    for (auto &rock : rocks) {
        delete rock;
    }
    delete rocket;
    window->tearDown();
    soundBoard->tearDown();
    delete soundBoard;
    delete window;
}