#include "Sound.h"


///////////
#include <windows.h>
#include <iostream>
#include <string>
///////////


CSound::CSound()
{
	//Init Sounds
		
	if (!soundbuffer[PIECE_MOVE].loadFromFile("./assets/Sounds/clicked.wav")
		|| !soundbuffer[PIECE_KILL].loadFromFile("./assets/Sounds/killthepiece.wav")
		|| !soundbuffer[PIECE_CHECK].loadFromFile("./assets/Sounds/check.wav")
		
		)
		std::cout << "Failed loading sounds" << std::endl;

}


CSound::~CSound()
{
}


bool CSound::Play_Sound(char cSoundType)
{

	sound.setBuffer(soundbuffer[cSoundType]);
	//sound.setVolume(50);
	sound.play();

	return true;

}
