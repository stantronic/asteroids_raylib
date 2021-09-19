#ifndef ASTEROIDS_SCENE_H
#define ASTEROIDS_SCENE_H


#include <vector>
#include "entities/Entity.h"
#include "entities/Rocket.h"
#include "entities/Rock.h"
#include "events/EventBus.h"

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
    Window *window;
    EventBus *events;
    GameState game_state;
    std::vector<Rock *> rocks;
    std::vector<Entity *> movables;
    std::vector<Bullet *> bullets;

    void onEvent(Event *e);

    bool allRocksGone();

    void reset();

};


#endif //ASTEROIDS_SCENE_H
