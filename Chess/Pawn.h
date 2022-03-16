#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
//#include "Queen.h"

#define UP		-1
#define DOWN	1

class Pawn :  public Piece

{
public:
	Pawn(int, int, int, char);
	~Pawn();

	std::vector<sf::Vector2i> getPossibleMoves(Array2D<Piece*>&) override;

private:
	int dir;

	//Queen *m_Queen = new Queen(100, 3, 0, 'b');
		
};

#endif