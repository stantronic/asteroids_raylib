#include "raylib.h"
#include "Constants.h"
#include "Window.h"
#include "SoundBoard.h"
#include "events/Event.h"
#include "Scene.h"
#include "events/EventNames.h"
#include "events/EventBus.h"

int main() {

    auto *window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    auto *sounds = new SoundBoard;
    auto *events = new EventBus(sounds);
    auto *scene = new Scene(window, events);

#ifdef LOG_EVENTS
    events->addListener([](Event* e) {
        printf(
                "Event: %d %s\n",
                e->type,
                EventNames::of(e->type).c_str()
        );
    });
#endif


    while (!WindowShouldClose()) {
        sounds->updateMusic();
        scene->update();
        BeginDrawing();
        window->draw();
        scene->draw();
        EndDrawing();
    }

    delete scene;
    delete sounds;
    delete events;
    delete window;
}