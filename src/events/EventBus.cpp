#include "EventBus.h"
#include "EventListener.h"
#include <iostream>

EventBus::~EventBus() {
    listeners.clear();
    sounds = nullptr;
}

void EventBus::addListener(Action &action) {
    listeners.push_back(new EventListener(action));
}

void EventBus::addListener(EventListener *listener) {
    listeners.push_back(listener);
}

void EventBus::send(Event *event) {
    for (auto l : listeners) {
        l->onEvent(event);
    }
    switch (event->type) {
        case ROCK_EXPLODE: {
            sounds->boom();
            auto r = (RockExplode *) event;
            std::cout << (r->coords.x) << std::endl;
        }
            break;
        case THRUST:
            sounds->thrust();
            break;
        case SHOOT: {
            auto r = (ShootEvent *) event;
            std::cout << (r->position.x) << std::endl;
            sounds->fire();
        }
            break;
        case LOSE:
            sounds->boom();
            break;
        case WIN:
            break;
    }

    delete event;
}

void EventBus::shoot(Vector2 position, Vector2 velocity, float angle) {
    send(new ShootEvent(position, velocity, angle));
}

void EventBus::thrust() {
    send(new Event(THRUST));
}