// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 27.07.2018.
//

#include <boost/filesystem.hpp>
#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer(fs::path music_dir)
: music_dir(music_dir)
{ }

void MusicPlayer::playUniqueRand() {
    // FIXME: Очень часто проверяется то, что изменяется относительно редко.
    // TODO: Ввести бы сюда как-то условную переменную для синхронизации...
    // А для её ввода нужно создать очереди сообщений... Много работы.
    
    if(!isMusicReadyToPlay()) {
        return;
    }
    
    // Обновим список (кэш) ещё не проигранных треков, если он опустел.
    // Список имён уже содержит хотя бы один трек.
    if(not_played_yet.empty()) {
        fillUniquePlaylist();
        randomSort(not_played_yet);
    }
    
    if(openMusic(not_played_yet.back())) {
        cur_music.play();
        not_played_yet.pop_back();
    } else {
        std::cerr << "Directory and playlist update, but music not found";
    }
    
}

void MusicPlayer::loadNames() {
    for(fs::directory_entry& file: fs::directory_iterator(music_dir)) {
        if(fs::is_regular_file(file) && fs::extension(file) == ".wav") {
            music_names.push_back(file.path().filename().string());
        }
    }
}
bool MusicPlayer::tryUpdatePlaylist() {
    if(!boost::filesystem::exists(music_dir)) {
        return false; // Музыки нет. Вечеринка отменяется.
	}
    
    // Обновим список существующей музыки, если папку с музыкой изменили.
    time_t cur_update_directory = fs::last_write_time(music_dir); //-V795
    if(cur_update_directory != last_update_music_dir) {
        last_update_music_dir = cur_update_directory;
        music_names.clear();
        loadNames();
        return true;
    }
    
    return false;
}
bool MusicPlayer::openMusic(NameIterator name_iterator) {
    // Любые другие способы проигрывания музыки должны ссылаться на
    // главный список с именами.
    return cur_music.openFromFile(music_dir.string() + *name_iterator);
}
bool MusicPlayer::isMusicReadyToPlay() {
    tryUpdatePlaylist(); // Удалось или нет - не так важно.
    bool music_exists = !music_names.empty();
    bool music_has_stopped = cur_music.getStatus() == sf::Music::Status::Stopped;
    return music_exists && music_has_stopped;
}

void MusicPlayer::fillUniquePlaylist() {
    // Обновим мини-кэш.
    auto& cache = not_played_yet;
    auto const& source = music_names;
    
    cache.resize(source.size());
    size_t j = 0;
    for(NameIterator i = source.begin(); i != source.end(); ++i) {
        cache[j++] = i;
    }
}
