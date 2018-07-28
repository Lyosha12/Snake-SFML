//
// Created by Lyosha12 on 27.07.2018.
//

#ifndef SNAKE_AUDIOPLAYER_HPP
#define SNAKE_AUDIOPLAYER_HPP

#include <memory>

#include "Utility/ThreadGuard/ThreadGuard.hpp"
#include "AudioPlayer/MusicPlayer/MusicPlayer.hpp"

class AudioController {
    // Управляет всеми звуками игры.
  public:
    AudioController()
    : cur_music(new MusicPlayer("Resources/Audio/Music/"))
    , thread([this](LiveStorage& alive) { run(alive); })
    { }
    void run(LiveStorage& alive) {
        while(alive) {
            cur_music->playUniqueRand();
        }
    }
    
  private:
    std::unique_ptr<MusicPlayer> cur_music;
    ThreadGuard thread;
};


#endif //SNAKE_AUDIOPLAYER_HPP
