//
// Created by Steven Stanton on 18/09/2021.
//

#include "Rock.h"

Rock::Rock(Vector2 pos, Vector2 vel, EventBus *events, float spin, int size) : Entity(),
                                                                               velocity(vel),
                                                                               events(events),
                                                                               spin(spin),
                                                                               rotation(spin),
                                                                               size(size) {
    position = pos;
    alive = true;
    collisionRecSize = (float) size * 1.4f;
}


