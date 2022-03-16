#pragma once

#include <SFML/Audio.hpp>


class CSound
{
public:
	CSound();
	~CSound();

	bool Play_Sound(char cSoundType);

	const char PIECE_MOVE = 0;
	const char PIECE_KILL = 1;
	const char PIECE_CHECK = 2;

private:
	sf::SoundBuffer soundbuffer[3];
	sf::Sound sound;
};

