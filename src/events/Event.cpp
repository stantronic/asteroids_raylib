#include "Event.h"

Event::Event(EventType type) : type(type) {}

RockExplode::RockExplode(Vector2 coords) : Event(ROCK_EXPLODE), coords(coords) {}

ShootEvent::ShootEvent(Vector2 p, Vector2 v, float a) :
        Event(SHOOT),
        position(p),
        velocity(v),
        angle(a) {}

Lose::Lose(Vector2 coords) : Event(LOSE), coords(coords) {}

