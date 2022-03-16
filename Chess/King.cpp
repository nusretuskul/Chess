#include "King.h"

King::King(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_king.png" : "./assets/black_king.png", _size, _col, _row, _colour, 'K',3)
{

}

King::~King()
{

}

std::vector<sf::Vector2i> King::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;

	for (int _dCol = -1; _dCol <= 1; ++_dCol)
	{
		for (int _dRow = -1; _dRow <= 1; ++_dRow)
		{
			int _nextCol = col + _dCol;
			int _nextRow = row + _dRow;

			if (_board.inBounds(_nextCol, _nextRow))
			{
				if (_board[_nextCol][_nextRow] && _board[_nextCol][_nextRow]->getColour() == getColour()) continue;

				_moves.push_back(sf::Vector2i(_nextCol, _nextRow));
			}
		}
	}

	if (move == 0)
	{
		Piece* _piece;

		if (_board[0][row] && _board[0][row]->getMove() == 0)
		{
			_piece = NULL;
			for (int _col = 1; _col < col; ++_col)
				if (!_piece) _piece = _board[_col][row];

			if (!_piece) _moves.push_back(sf::Vector2i(0, row));
		}

		if (_board[_board.getCols() - 1][row] && _board[_board.getCols() - 1][row]->getMove() == 0)
		{
			_piece = NULL;
			for (int _col = col + 1; _col < _board.getCols() - 1; ++_col)
				if (!_piece) _piece = _board[_col][row];

			if (!_piece) _moves.push_back(sf::Vector2i(_board.getCols() - 1, row));
		}
	}

	return _moves;
}