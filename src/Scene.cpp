#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-slicing"
//
// Created by Steven Stanton on 15/09/2021.
//

#include "Scene.h"
#include "Rock.h"
#include "Utils.h"

Scene::Scene(Window *window, EventBus *events) : window(window), events(events) {
    game_state = PLAYING;
    rocket = new Rocket{window, events};
    reset();
}

void Scene::reset() {

    rocks.clear();
    movables.clear();
    movables.push_back((Movable *) rocket);
    rocks.reserve(3);
    rocks.emplace_back(Rock::make({100, 100}, {5, 2}, events));
    rocks.emplace_back(Rock::make({200, 200}, {4, 9}, events));
    rocks.emplace_back(Rock::make({500, 800}, {-5, -2}, events));
    movables.push_back((Movable *) rocks[0]);
    movables.push_back((Movable *) rocks[1]);
    movables.push_back((Movable *) rocks[2]);
    rocket->positionAt(window->getCenter());
    rocket->revive();
    game_state = PLAYING;
}

bool Scene::allRocksGone() {
    for (auto &r : rocks) {
        if (r->isAlive()) return false;
    }
    return true;
}

void Scene::update() {

    if (game_state != PLAYING && IsKeyDown(KEY_R)) {
        reset();
    }
    for (Movable *m : movables) {
        m->update(window);
    }

    for (auto &rock : rocks) {
        if (rock->isAlive()
            && rocket->isAlive()
            && rocket->fireHitsRock(rock->getCollisionRec())) {
            rock->explode();
            events->send(RockExplode(rock->getPosition()));
            auto *explosion = new Explosion(BLUE);
            explosion->explode(rock->getPosition());
            movables.push_back(explosion);
            if (allRocksGone()) {
                events->send(Event(WIN));
                game_state = WON;
            }
        }

        if (areColliding(rock, rocket)) {
            rocket->explode();

            auto *explosion = new Explosion(RED);
            explosion->explode(rocket->getPosition());
            movables.push_back(explosion);
            events->send(Lose(rocket->getPosition()));
            game_state = LOST;
        }
    }

}

void Scene::draw() {
    for (Movable *m : movables) {
        m->draw();
    }
    switch (game_state) {

        case PLAYING:
            break;
        case WON:
            DrawText("You win", 100, 100, 40, WHITE);
            DrawText("Press 'R' to play again", 100, 200, 20, YELLOW);
            break;
        case LOST:
            DrawText("You lose", 100, 100, 40, WHITE);
            DrawText("Press 'R' to play again", 100, 200, 20, YELLOW);
            break;
    }
}

Scene::~Scene() {
    rocks.clear();
    movables.clear();
    delete rocket;
    window = nullptr;
    events = nullptr;
}

#pragma clang diagnostic pop