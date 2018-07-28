//
// Created by Lyosha12 on 27.07.2018.
//

#include "AudioController.hpp"

AudioController::AudioController()
    : cur_music(new MusicPlayer("Resources/Audio/Music/"))
    , thread([this](LiveStorage& alive) { run(alive); })
{ }
void AudioController::run(LiveStorage& alive) {
    while(alive) {
        cur_music->playUniqueRand();
    }
}