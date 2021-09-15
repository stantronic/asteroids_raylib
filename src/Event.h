//
// Created by Steven Stanton on 15/09/2021.
//

#ifndef ASTEROIDS_EVENT_H
#define ASTEROIDS_EVENT_H

#include <raylib.h>
#include <vector>
#include "SoundBoard.h"
#include <map>
#include <string>


enum EventType {
    SHOOT,
    THRUST,
    ROCK_EXPLODE,
    WIN,
    LOSE,
};

class EventNames {
public:
    static std::map<EventType, std::string> names;

    static char *of(EventType eventType);
};


struct Event {
    EventType type;

    explicit Event(EventType type) : type(type) {}
};

typedef void(*Action)(Event);

struct RockExplode : Event {
    Vector2 coords;

    explicit RockExplode(Vector2 coords) : Event(ROCK_EXPLODE), coords(coords) {}
};

struct Lose : Event {
    Vector2 coords;

    explicit Lose(Vector2 coords) : Event(LOSE), coords(coords) {}
};


class EventListener {
public:
    explicit EventListener(Action action, int type) : action(action), type(type) {}

    explicit EventListener(Action action) : action(action), type(-1) {}

    void onEvent(Event event) {
        if (type == event.type || type == -1) {
            action(event);
        }
    }

    Action action;
    int type;
};

class EventBus {
public:
    explicit EventBus(SoundBoard *sounds) : sounds(sounds) {}
    ~EventBus();

    void shoot();

    void thrust();

    void send(Event event);

    void addListener(EventListener *listener);

    void addListener(Action action);

private:
    SoundBoard *sounds;
    std::vector<EventListener *> listeners;
};

#endif //ASTEROIDS_EVENT_H
