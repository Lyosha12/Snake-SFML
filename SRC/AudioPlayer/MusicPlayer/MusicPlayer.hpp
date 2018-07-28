//
// Created by Lyosha12 on 27.07.2018.
//

#ifndef SNAKE_MUSICPLAYER_HPP
#define SNAKE_MUSICPLAYER_HPP


#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>
#include <Utility/RandomSort.hpp>

#include "Utility/RandomGenerator/RandomGenerator.hpp"

namespace fs = boost::filesystem;

#include "Utility/Timer.hpp"

class MusicPlayer {
    // Проигрывает длительную wav-музыку.
    
    using NameIterator = std::vector<std::string>::iterator;
  public:
    MusicPlayer(fs::path music_dir): music_dir(music_dir) {
        loadNames(music_dir);
    }
    
    void playUniqueRand() {
        if(isMusicPlay()) {
            return;
        }
        
        if(tryUpdatePlaylist() || not_played_yet.empty()) {
            fillUniquePlaylist();
            randomSort(not_played_yet);
        }
        
        if(openMusic(not_played_yet.back())) {
            cur_music.play();
        } else {
            std::cerr << "Directory and playlist update, but music not found";
        }
    
        not_played_yet.pop_back();
    }
    
  private:
    void loadNames(fs::path music_dir) {
        for(fs::directory_entry& file: fs::directory_iterator(music_dir)) {
            if(fs::is_regular_file(file) && fs::extension(file) == ".wav")
                music_names.push_back(file.path().filename().string());
        }
    }
    bool tryUpdatePlaylist() {
        time_t cur_update_directory = fs::last_write_time(music_dir);
        if(cur_update_directory != last_update_directory) {
            last_update_directory = cur_update_directory;
            loadNames(music_dir);
            return true;
        }
        
        return false;
    }
    bool openMusic(NameIterator name_iterator) {
        return cur_music.openFromFile(music_dir.string() + *name_iterator);
    }
    bool isMusicPlay() {
        tryUpdatePlaylist();
        return cur_music.getStatus() == sf::Music::Status::Playing;
    }
    
    void fillUniquePlaylist() {
        for(auto i = music_names.begin(); i != music_names.end(); ++i) {
            not_played_yet.push_back(i);
        }
    }
  
  private:
    std::vector<std::string> music_names;
    std::vector<NameIterator> not_played_yet;
    fs::path music_dir;
    time_t last_update_directory = fs::last_write_time(music_dir);
    
    sf::Music cur_music;
};


#endif //SNAKE_MUSICPLAYER_HPP
