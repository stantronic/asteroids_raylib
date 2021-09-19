#include "EventListener.h"

EventListener::EventListener(Action action, int type) : action(action), type(type) {}

EventListener::EventListener(Action action) : action(action), type(-1) {}

void EventListener::onEvent(Event *event) {
    if (type == event->type || type == -1) {
        action(event);
    }
}

int EventListener::getType() {
    return type;
}