#ifndef ASTEROIDS_EVENTBUS_H
#define ASTEROIDS_EVENTBUS_H

#include "Event.h"
#include "EventListener.h"

class EventBus {
public:
    explicit EventBus(SoundBoard *sounds) : sounds(sounds) {}

    ~EventBus();

    void shoot(Vector2 position, Vector2 velocity, float angle);

    void thrust();

    void send(Event *event);

    void addListener(EventListener *listener);

    void addListener(Action &action);

private:
    SoundBoard *sounds;
    std::vector<EventListener *> listeners;
};


#endif //ASTEROIDS_EVENTBUS_H
