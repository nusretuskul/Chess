#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Window.h"
#include "GUI.h"

const std::string TITLE = "Chess";
const unsigned int FRAMERATE = 60;
const unsigned int GUI_WIDTH = 200;

class Game
{
public:
	Game();

	void start();
	void stop();
	void cleanup();

private:
	void gameloop();
	void getInput();
	void update(float);
	void render();
	void initGUI();

	Board* board;
	Window* window;
	GUI* gui;

	bool running;
};

#endif