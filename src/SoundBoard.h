#ifndef SOUND_BOARD
#define SOUND_BOARD

#include "raylib.h"

class SoundBoard {
public:
    SoundBoard() {
        InitAudioDevice();
        SetMasterVolume(0.4f);
        explosion = LoadSound("sounds/boom.ogg");
        boost = LoadSound("sounds/boost.mp3");
        shoot = LoadSound("sounds/shoot.ogg");

        music = LoadMusicStream("sounds/music2.mp3");

        PlayMusicStream(music);
        SetMusicVolume(music, 1.0f);
    }

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