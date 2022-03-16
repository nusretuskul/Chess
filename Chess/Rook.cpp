#include "Rook.h"

Rook::Rook(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_rook.png" : "./assets/black_rook.png", _size, _col, _row, _colour, 'r',2)
{

}

Rook::~Rook()
{

}

std::vector<sf::Vector2i> Rook::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;

	int _colBounds[2];
	int _rowBounds[2];

	_colBounds[0] = _rowBounds[0] = -1;
	_colBounds[1] = _rowBounds[1] = _board.getCols();

	for (int _delta = 1; _delta < _board.getCols(); ++_delta)
	{
		for (int _multiple = -1; _multiple <= 1; _multiple += 2)
		{
			int _index = _multiple < 0 ? 0 : 1;
			int _nullBounds = _multiple < 0 ? -1 : _board.getCols();

			if (_board.inBounds(col + _delta * _multiple, row))
			{
				if (_board[col + _delta * _multiple][row] && _colBounds[_index] == _nullBounds)
				{
					_colBounds[_index] = col + _delta * _multiple;
					if (_board[col + _delta * _multiple][row]->getColour() == getColour())
						_colBounds[_index] -= _multiple;
				}

				if ((_multiple < 0 && col + _delta * _multiple >= _colBounds[_index]) || (_multiple > 0 && col + _delta * _multiple <= _colBounds[_index]))
					_moves.push_back(sf::Vector2i(col + _delta * _multiple, row));
			}

			if (_board.inBounds(col, row + _delta * _multiple))
			{
				if (_board[col][row + _delta * _multiple] && _rowBounds[_index] == _nullBounds)
				{
					_rowBounds[_index] = row + _delta * _multiple;
					if (_board[col][row + _delta * _multiple]->getColour() == getColour())
						_rowBounds[_index] -= _multiple;
				}

				if ((_multiple < 0 && row + _delta * _multiple >= _rowBounds[_index]) || (_multiple > 0 && row + _delta * _multiple <= _rowBounds[_index]))
					_moves.push_back(sf::Vector2i(col, row + _delta * _multiple));
			}
		}
	}

	return _moves;
}