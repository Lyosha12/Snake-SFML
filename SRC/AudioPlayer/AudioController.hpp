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
    AudioController();
    
    // Запускается в отдельном потоке.
    void run(LiveStorage& alive);
    
  private:
    // TODO: Потом можно сделать массив проигрывателей для разных меню.
    std::unique_ptr<MusicPlayer> cur_music;
    
    // TODO: Т.к. работает в отдельном потоке, нужна очередь для общения.
    ThreadGuard thread;
};


#endif //SNAKE_AUDIOPLAYER_HPP
