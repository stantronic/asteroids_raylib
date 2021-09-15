//
// Created by Steven Stanton on 15/09/2021.
//

#ifndef ASTEROIDS_SCENE_H
#define ASTEROIDS_SCENE_H


#include <vector>
#include "Movable.h"
#include "Rocket.h"
#include "Rock.h"

enum GameState {
    PLAYING,
    WON,
    LOST
};

class Scene {
public:
    explicit Scene(Window *window, EventBus *events);

    ~Scene();

    void update();

    void draw();

private:
    Rocket *rocket;
    std::vector<Rock *> rocks;
    std::vector<Movable *> movables;
    Window *window;
    EventBus *events;
    GameState game_state;

    bool allRocksGone();

    void reset();
};


#endif //ASTEROIDS_SCENE_H
