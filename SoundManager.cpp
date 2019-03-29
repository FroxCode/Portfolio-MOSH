//Created by Connor Maguire
//Pump up the jams
#include "SoundManager.h"
SoundManager::SoundManager(){}
SoundManager::~SoundManager(){}

void SoundManager::reCreate(const std::string & file, int volume){

	s.loadFromFile(file);
	m_sound.setBuffer(s);
	m_sound.setVolume(volume);
}

void SoundManager::playSingle(){

	m_sound.play();			//plays once

}
void SoundManager::playLoop(){

	m_sound.setLoop(true);			//loops (used for background music)
	m_sound.play();

}
void SoundManager::adjustVolume(int vol){

	m_sound.setVolume(m_sound.getVolume() + vol);			//change the volume(passed an integer value from 1-10)
}
void SoundManager::setVolume(int vol){

	m_sound.setVolume(vol);			//change the volume(passed an integer value from 1-10)
}
void SoundManager::stopPlay(){

	m_sound.stop();

}
int SoundManager::getVolume(){

	return m_sound.getVolume();
}