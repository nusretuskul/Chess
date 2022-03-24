#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

#include "Window.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Array2D.h"
#include "Sound.h"

#define PLAYER_ONE	'w'
#define PLAYER_TWO	'b'

const unsigned int COLS = 8;
const unsigned int ROWS = 8;
const unsigned int TILE_SIZE = 100;




class Board
{
public:
	Board();
	~Board();

	void init();
	void update();
	void render(Window*);
	void mouseClicked(sf::Vector2i);
	void resetBoard();

	int getCols();
	int getRows();
	int getTileSize();

	void switchTakeTurns();



private:
	void checkPossibleMoves(int, int);
	//NUSRET
	//
	bool IsCheckState(Piece* Piece, std::vector<sf::Vector2i> posMoves, char playercolour);
	void GetPossibleBlockCheck();
	void SavePotentiallyCheckPosition();
	char GetChecktype();
	void ControlAnyCheckPosition();
	void CheckHeroPawnAndMakeQueen();
	void ControlCastling(const int &_col, const int &_row);
	void ControlEnPassant(const int& _col, const int& _row);

	Array2D<Piece*> board = Array2D<Piece*>(COLS, ROWS);
	Piece* selectedPiece;
	std::vector<sf::Vector2i> possibleMoves;

	//Nusret
	Piece* killerPiece;
	std::vector<sf::Vector2i> killerPossibleMoves;
	std::vector<sf::Vector2i> PotentiallyCheckMoves;
	std::vector<sf::Vector2i> PossibleMovesForBlockCheck;
	

	char curPlayer;
	bool takeTurns;
	CSound sound;

	//NUSRET
	char cSoundType = NULL;
	bool isCheck = false;
	bool isPossibleBlockCheck = false;
	char kingcurcol = 0;
	char kingcurrow = 0;


};

#endif