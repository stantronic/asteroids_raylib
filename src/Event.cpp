#include "Event.h"

std::map<EventType, std::string> EventNames::names = std::map<EventType, std::string>{
        {SHOOT,        "Shoot"},
        {THRUST,       "Thrust"},
        {ROCK_EXPLODE, "Rock explodes"},
        {WIN,          "Win"},
        {LOSE,         "Lose"},
};

char *EventNames::of(EventType type) {
    return (char *) names[type].c_str();
}

EventBus::~EventBus() {
    listeners.clear();
    sounds = nullptr;
}

void EventBus::addListener(Action action) {
    listeners.push_back(new EventListener(action));
}

void EventBus::addListener(EventListener *listener) {
    listeners.push_back(listener);
}

void EventBus::send(Event event) {
    for (auto l : listeners) {
        l->onEvent(event);
    }
    switch (event.type) {
        case ROCK_EXPLODE:
            sounds->boom();
            break;
        case THRUST:
            sounds->thrust();
            break;
        case SHOOT:
            sounds->fire();
            break;
        case LOSE:
            sounds->boom();
            break;
        case WIN:
        default:
            break;
    }
}

void EventBus::shoot() {
    send(Event(SHOOT));
}

void EventBus::thrust() {
    send(Event(THRUST));
}
