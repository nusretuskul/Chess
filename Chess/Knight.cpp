#include "Knight.h"

Knight::Knight(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_knight.png" : "./assets/black_knight.png", _size, _col, _row, _colour, 'k',0)
{

}

Knight::~Knight()
{

}

std::vector<sf::Vector2i> Knight::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;
	int _dCol = -2;
	int _dRow = -1;

	for (int _i = 0; _i < 4; ++_i)
	{
		if (_board.inBounds(col + _dCol, row + _dRow) && (!_board[col + _dCol][row + _dRow] || 
			(_board[col + _dCol][row + _dRow] && _board[col + _dCol][row + _dRow]->getColour() != getColour())))
		{
			_moves.push_back(sf::Vector2i(col + _dCol, row + _dRow));
		}

		if (_board.inBounds(col + _dRow, row + _dCol) && (!_board[col + _dRow][row + _dCol] ||
			(_board[col + _dRow][row + _dCol] && _board[col + _dRow][row + _dCol]->getColour() != getColour())))
		{
			_moves.push_back(sf::Vector2i(col + _dRow, row + _dCol));
		}

		int _temp = _dCol;
		_dCol = _dRow;
		_dRow = -_temp;
	}

	return _moves;
}