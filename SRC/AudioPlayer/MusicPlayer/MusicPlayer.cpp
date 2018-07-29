//
// Created by Lyosha12 on 27.07.2018.
//

#include <boost/filesystem.hpp>
#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer(fs::path music_dir): music_dir(music_dir) { }

void MusicPlayer::playUniqueRand() {
    // FIXME: Очень часто проверяется то, что изменяется относительно редко.
    // TODO: Ввести бы сюда как-то условную переменную для синхронизации...
    // А для её ввода нужно создать очереди сообщений... Много работы.
    if(!isMusicReadyToPlay()) {
        return;
    }
    
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

void MusicPlayer::loadNames(fs::path music_dir) {
    if(!boost::filesystem::exists(music_dir)) {
        return; // Музыка полностью опциональна.
    }
    
    for(fs::directory_entry& file: fs::directory_iterator(music_dir)) {
        if(fs::is_regular_file(file) && fs::extension(file) == ".wav") {
            music_names.push_back(file.path().filename().string());
        }
    }
}
bool MusicPlayer::tryUpdatePlaylist() {
    time_t cur_update_directory = fs::last_write_time(music_dir);
    if(cur_update_directory != last_update_directory) {
        last_update_directory = cur_update_directory;
        loadNames(music_dir);
        return true;
    }
    
    return false;
}
bool MusicPlayer::openMusic(NameIterator name_iterator) {
    return cur_music.openFromFile(music_dir.string() + *name_iterator);
}
bool MusicPlayer::isMusicReadyToPlay() {
    tryUpdatePlaylist();
    bool music_exists = !music_names.empty();
    bool music_has_stopped = cur_music.getStatus() == sf::Music::Status::Stopped;
    return music_exists && music_has_stopped;
}

void MusicPlayer::fillUniquePlaylist() {
    for(auto i = music_names.begin(); i != music_names.end(); ++i) {
        not_played_yet.push_back(i);
    }
}
