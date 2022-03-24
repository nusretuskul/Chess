#ifndef KING_H
#define KING_H

#include "Piece.h"


class King : public Piece
{
public:
	King(int, int, int, char);
	~King();

	std::vector<sf::Vector2i> getPossibleMoves(Array2D<Piece*>&) override;


private:
	bool CheckRookUnderThreat(Array2D<Piece*>& _board, const char rookcol, const char rookrow);

};

#endif

