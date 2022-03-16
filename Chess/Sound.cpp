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

	//./assets/Sounds/

		//TCHAR path[MAX_PATH + 1] = L"";
		//DWORD len = GetCurrentDirectory(MAX_PATH, path);
		//printf(" directory is %S \n", path);

	sound.setBuffer(soundbuffer[cSoundType]);
	//sound.setVolume(50);
	sound.play();

	//	while (sound.getStatus() == sf::Sound::Playing)
	//	{
			// Leave some CPU time for other processes
			//sf::sleep(sf::milliseconds(1000));

			// Display the playing position
	//		std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
	//		std::cout << std::flush;
	//	}

	return true;

}
