//
// Created by Lyosha12 on 27.07.2018.
//

#ifndef SNAKE_MUSICPLAYER_HPP
#define SNAKE_MUSICPLAYER_HPP


#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>

#include "Utility/RandomSort.hpp"

#include "Utility/RandomGenerator/RandomGenerator.hpp"

namespace fs = boost::filesystem;

#include "Utility/Timer.hpp"

// TODO: Добавить возможность паузы, остановки
class MusicPlayer {
    // Проигрывает длительную wav-музыку.
    
    using NameIterator = std::vector<std::string>::const_iterator;
  public:
    MusicPlayer(fs::path music_dir);
    
    // * Из существующей директории с музыкой загружаются имена файлов,
    //   случайно сортируются и проигрываются по одному файлу.
    // * При исчерпании этого случайно отсортированного списка повторяем.
    void playUniqueRand();
    
    
  private:
    void loadNames();
    bool tryUpdatePlaylist();
    bool openMusic(NameIterator name_iterator);
    bool isMusicReadyToPlay();
    
    void fillUniquePlaylist();
  
  private:
    fs::path const music_dir;
    std::vector<std::string> music_names;     // Имена файлов из music_dir.
    std::vector<NameIterator> not_played_yet;
    time_t last_update_music_dir = 0; //-V795
    
    sf::Music cur_music;
};


#endif //SNAKE_MUSICPLAYER_HPP
