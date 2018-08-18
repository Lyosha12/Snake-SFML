// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 27.07.2018.
//

#include <Utility/FatalError/FatalError.hpp>
#include "AudioController.hpp"

AudioController::AudioController()
    : cur_music(new MusicPlayer("../Resources/Audio/Music/"))
    , thread([this](LiveStorage& alive) { run(alive); })
{ }
void AudioController::run(LiveStorage& alive) {
    try {
        while(alive) {
            // TODO: Тут бы обработку сообщений из внешнего источника.
            cur_music->playUniqueRand();
        }
    }
    
    // Ошибки, не совместимые с жизнью приложения.
    catch(fs::filesystem_error const& e) {
        FatalError(e.what()).print();
    }
    catch(std::exception const& e) {
        FatalError(e.what()).print();
    }
    catch(...) {
        FatalError("Audio controller throws unexpected exception").print();
    }
}