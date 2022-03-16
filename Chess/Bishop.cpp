#include "Bishop.h"

Bishop::Bishop(int _size, int _col, int _row, char _colour)
	: Piece(_colour == 'w' ? "./assets/white_bishop.png" : "./assets/black_bishop.png", _size, _col, _row, _colour, 'b',1)
{

}

Bishop::~Bishop()
{

}

std::vector<sf::Vector2i> Bishop::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;

	// Even Index : Column | Odd Index : Row
	// 0, 1: Top Left | -1, -1
	// 2, 3: Top Right | 1, -1
	// 4, 5: Bottom Left | -1, 1
	// 6, 7: Bottom Right | 1, 1
	int _bounds[8];
	_bounds[0] = _bounds[1] = _bounds[3] = _bounds[4] = -1;
	_bounds[2] = _bounds[6] = _board.getCols();
	_bounds[5] = _bounds[7] = _board.getRows();

	for (int _delta = 1; _delta < _board.getCols(); ++_delta)
	{
		for (int _rad = 1; _rad <= 4; ++_rad)
		{
			int _colMultiple = (int)cos(_rad * M_PI);
			int _rowMultiple = -(int)cos(floor((_rad - 1) / 2) * M_PI);

			int _nullColBounds = _colMultiple < 0 ? -1 : _board.getCols();
			int _nullRowBounds = _rowMultiple < 0 ? -1 : _board.getRows();

			int _colIndex = (_rad - 1) * 2;
			int _rowIndex = _rad * 2 - 1;

			int _nextCol = col + _delta * _colMultiple;
			int _nextRow = row + _delta * _rowMultiple;

			//std::cout << _colMultiple << ", " << _rowMultiple << " | " << _nullColBounds << ", " << _nullRowBounds << " | " << _colIndex << ", " << _rowIndex << " | " << _nextCol << ", " << _nextRow << std::endl;

			if (_board.inBounds(_nextCol, _nextRow))
			{
				if (_board[_nextCol][_nextRow])
				{
					if (_bounds[_colIndex] == _nullColBounds)
						_bounds[_colIndex] = _nextCol;

					if (_bounds[_rowIndex] == _nullRowBounds)
						_bounds[_rowIndex] = _nextRow;

					if (_board[_nextCol][_nextRow]->getColour() == getColour())
					{
						_bounds[_colIndex] -= _colMultiple;
						_bounds[_rowIndex] -= _rowMultiple;
					}
				}

				if (((_colMultiple < 0 && _nextCol >= _bounds[_colIndex]) || (_colMultiple > 0 && _nextCol <= _bounds[_colIndex])) &&
					((_rowMultiple < 0 && _nextRow >= _bounds[_rowIndex]) || (_rowMultiple > 0 && _nextRow <= _bounds[_rowIndex])))
					_moves.push_back(sf::Vector2i(_nextCol, _nextRow));
			}
		}
	}

	return _moves;
}