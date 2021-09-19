//
// Created by Steven Stanton on 17/09/2021.
//

#ifndef ASTEROIDS_EVENTNAMES_H
#define ASTEROIDS_EVENTNAMES_H
#include <raylib.h>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include "../SoundBoard.h"

enum EventType {
    SHOOT,
    THRUST,
    ROCK_EXPLODE,
    WIN,
    LOSE,
};

class EventNames {
public:

    static std::string of(EventType eventType) {
        return Get().names[eventType];
    }

    EventNames(const EventNames &) = delete;

    static EventNames &Get() {
        static EventNames instance;
        return instance;
    };

private:
    EventNames(); // NOLINT(hicpp-use-equals-delete,modernize-use-equals-delete)

    std::map<EventType, std::string> names;
};

#endif //ASTEROIDS_EVENTNAMES_H
