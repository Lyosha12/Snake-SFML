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
    MusicPlayer(fs::path music_dir);
    
    void playUniqueRand();
    
  private:
    void loadNames(fs::path music_dir);
    bool tryUpdatePlaylist();
    bool openMusic(NameIterator name_iterator);
    bool isMusicReadyToPlay();
    
    void fillUniquePlaylist();
  
  private:
    std::vector<std::string> music_names;
    std::vector<NameIterator> not_played_yet;
    fs::path music_dir;
    time_t last_update_directory = 0;
    
    sf::Music cur_music;
};


#endif //SNAKE_MUSICPLAYER_HPP
