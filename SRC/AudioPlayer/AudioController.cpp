//
// Created by Lyosha12 on 27.07.2018.
//

#include <Utility/ErrorPrinter/ErrorPrinter.hpp>
#include "AudioController.hpp"

AudioController::AudioController()
    : cur_music(new MusicPlayer("../Resources/Audio/Music/"))
    , thread([this](LiveStorage& alive) { run(alive); })
{ }
void AudioController::run(LiveStorage& alive) {
    try {
        while(alive) {
            cur_music->playUniqueRand();
        }
    }
    
    catch(fs::filesystem_error const& e) {
        ErrorPrinter(e.what()).print();
    }
    
    catch(std::exception const& e) {
        ErrorPrinter(e.what()).print();
    }
}