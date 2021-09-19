//
// Created by Steven Stanton on 17/09/2021.
//

#include "Event.h"
#include <iostream>
#include "EventNames.h"

EventNames::EventNames() {
    names = std::map<EventType, std::string>{
            {SHOOT,        "Shoot"},
            {THRUST,       "Thrust"},
            {ROCK_EXPLODE, "Rock explodes"},
            {WIN,          "Win"},
            {LOSE,         "Lose"},
    };
}