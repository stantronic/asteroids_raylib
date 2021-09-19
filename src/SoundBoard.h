#ifndef SOUND_BOARD
#define SOUND_BOARD

#include "raylib.h"

class SoundBoard {
public:
    SoundBoard();

    void boom() {
        PlaySound(explosion);
    }

    void fire() {
        PlaySound(shoot);
    }

    void thrust() {
        PlaySound(boost);
    }

    void updateMusic() {
        UpdateMusicStream(music);
    }

    ~SoundBoard() {
        UnloadSound(explosion);
        UnloadSound(boost);
        UnloadSound(shoot);
        UnloadMusicStream(music);
        CloseAudioDevice();
    }

private:
    Sound explosion{nullptr};
    Sound boost{nullptr};
    Sound shoot{nullptr};
    Music music{nullptr};
};

#endif