#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

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

		
};

#endif