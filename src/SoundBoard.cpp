#include "SoundBoard.h"

SoundBoard::SoundBoard() {
    InitAudioDevice();
    SetMasterVolume(0.4f);
    explosion = LoadSound("sounds/boom.ogg");
    boost = LoadSound("sounds/boost.mp3");
    shoot = LoadSound("sounds/shoot.ogg");

    music = LoadMusicStream("sounds/music2.mp3");

    PlayMusicStream(music);
    SetMusicVolume(music, 1.0f);
}
