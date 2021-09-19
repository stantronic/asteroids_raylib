#ifndef ASTEROIDS_EVENTLISTENER_H
#define ASTEROIDS_EVENTLISTENER_H

#include "Event.h"

class EventListener {
public:
    explicit EventListener(Action action, int type);

    explicit EventListener(Action action);

    void onEvent(Event *event);

    int getType();

private:
    int type;
    Action action;
};


#endif //ASTEROIDS_EVENTLISTENER_H
