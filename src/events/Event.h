#ifndef ASTEROIDS_EVENT_H
#define ASTEROIDS_EVENT_H

#include <raylib.h>
#include <vector>
#include "../SoundBoard.h"
#include "EventNames.h"
#include <map>
#include <string>
#include <functional>


struct Event {
    EventType type;

    explicit Event(EventType type);
};

typedef const std::function<void(Event *)> Action;

struct RockExplode : Event {
    Vector2 coords;

    explicit RockExplode(Vector2 coords);
};

struct ShootEvent : Event {
    Vector2 position;
    Vector2 velocity;
    float angle;

    explicit ShootEvent(Vector2 p, Vector2 v, float a);
};

struct Lose : Event {
    Vector2 coords;

    explicit Lose(Vector2 coords);
};


#endif //ASTEROIDS_EVENT_H
