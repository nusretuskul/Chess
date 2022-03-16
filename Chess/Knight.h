#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(int, int, int, char);
	~Knight();

	std::vector<sf::Vector2i> getPossibleMoves(Array2D<Piece*>&) override;

private:

};

#endif