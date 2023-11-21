#pragma once

#include "main.h"

void playSound(string soundName){
    sf::SoundBuffer buffer;
    string filename = "data/sound/" + soundName + ".mp3";
    if (!buffer.loadFromFile(filename))
        return;
    
    sf::Sound sound(buffer);
    sound.play();

    while (sound.getStatus() == sf::Sound::Playing){
        sf::sleep(sf::milliseconds(100));
    }
}