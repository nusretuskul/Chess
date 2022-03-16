#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(int, int, int, char);
	~Queen();

	std::vector<sf::Vector2i> getPossibleMoves(Array2D<Piece*>&) override;

private:

};

#endif

