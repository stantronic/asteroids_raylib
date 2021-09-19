#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-slicing"

#include "Scene.h"
#include "entities/Rock.h"
#include "Utils.h"
#include "events/EventBus.h"

Scene::Scene(Window *window, EventBus *events) : window(window), events(events) {
    game_state = PLAYING;
    rocket = new Rocket{window, events};
    events->addListener([&](Event *e) {
        this->onEvent(e);
    });
    reset();
}

void Scene::reset() {

    rocks.clear();
    movables.clear();
    bullets.clear();


    movables.push_back((Entity *) rocket);
    rocks.reserve(3);
    rocks.emplace_back(Rock::make({100, 100}, {5, 2}, 60, 3, events));
    rocks.emplace_back(Rock::make({200, 200}, {4, 9}, 60, -5, events));
    rocks.emplace_back(Rock::make({500, 800}, {-5, -2}, 60, 2, events));
    movables.push_back((Entity *) rocks[0]);
    movables.push_back((Entity *) rocks[1]);
    movables.push_back((Entity *) rocks[2]);
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
    for (auto &m : movables) {

        m->update(window);
    }

    for (auto rock : rocks) {

        for (auto bullet : bullets) {
            if (areColliding(rock, bullet)) {
                bullet->kill();
                rock->explode();
                events->send(new RockExplode(rock->getPosition()));
                auto *explosion = new Explosion(BLUE);
                explosion->explode(rock->getPosition());
                movables.push_back(explosion);
                if (rock->getSize() == 60) {
                    auto smallerRock1 = Rock::make(rock->getPosition(),
                                                   Vector2Scale(Vector2Rotate(bullet->getVelocity(), -20), 0.7),
                                                   40,
                                                   -9.f,
                                                   events);
                    auto smallerRock2 = Rock::make(rock->getPosition(),
                                                   Vector2Scale(Vector2Rotate(bullet->getVelocity(), 20), 0.7),
                                                   40,
                                                   9.f,
                                                   events);
                    rocks.emplace_back(smallerRock1);
                    rocks.emplace_back(smallerRock2);
                    movables.push_back(smallerRock1);
                    movables.push_back(smallerRock2);
                }
                if (rock->getSize() == 40) {
                    auto smallerRock1 = Rock::make(rock->getPosition(),
                                                   Vector2Scale(Vector2Rotate(bullet->getVelocity(), -30), 0.9),
                                                   20,
                                                   -15.f,
                                                   events);
                    auto smallerRock2 = Rock::make(rock->getPosition(),
                                                   Vector2Scale(Vector2Rotate(bullet->getVelocity(), 30), 0.9),
                                                   20,
                                                   15.f,
                                                   events);
                    rocks.emplace_back(smallerRock1);
                    rocks.emplace_back(smallerRock2);
                    movables.push_back(smallerRock1);
                    movables.push_back(smallerRock2);
                }
                if (allRocksGone()) {
                    events->send(new Event(WIN));
                    game_state = WON;
                }
            }
        }

        if (areColliding(rock, rocket)) {
            rocket->explode();
            auto *explosion = new Explosion(RED);
            explosion->explode(rocket->getPosition());
            movables.push_back(explosion);
            events->send(new Lose(rocket->getPosition()));
            game_state = LOST;
        }
    }

}

void Scene::draw() {
    for (Entity *m : movables) {
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
    bullets.clear();
    delete rocket;
    window = nullptr;
    events = nullptr;
}

void Scene::onEvent(Event *e) {
    switch (e->type) {
        case SHOOT:
            std::cout << "there are " << bullets.size() << " bullets\n";
            auto *shootEvent = (ShootEvent *) e;
            Bullet *b = nullptr;
            if (bullets.size() >= MAX_BULLETS) {
                for (auto &eachBullet: bullets) {
                    if (!eachBullet->isAlive()) {
                        b = eachBullet;
                        break;
                    }
                }
            } else {
                b = new Bullet{};
                bullets.push_back(b);
                movables.push_back(b);
            }
            if (b != nullptr) {
                b->shoot(shootEvent->position, shootEvent->velocity, shootEvent->angle);
            }
            break;
    }
}

#pragma clang diagnostic pop