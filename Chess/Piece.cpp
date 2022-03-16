#include "Piece.h"

Piece::Piece(std::string _file, int _size, int _col, int _row, char _colour, char _piece, char _movementtype)
	: move(0), selected(false), size(_size), col(_col), row(_row), colour(_colour), piece(_piece), movementtype(_movementtype)
{

	if (!tex.loadFromFile(_file))//////////
		std::cout << "Error loading file: " << _file << std::endl;

	rect.setSize(sf::Vector2f(size, size));
	rect.setOrigin(sf::Vector2f(size / 2, size / 2));
	rect.setPosition(sf::Vector2f(col * size + size / 2, row * size + size / 2));
	rect.setTexture(&tex);
	rect.setOutlineColor(sf::Color::Green);
}

Piece::~Piece()
{

}

void Piece::render(Window* _window)
{
	_window->render(rect);
}

void Piece::mouseClicked()
{
	selected = true;
	rect.setScale(sf::Vector2f(.96, .96));
	rect.setOutlineThickness(3);
}

void Piece::reset()
{
	selected = false;
	rect.setScale(sf::Vector2f(1, 1));
	rect.setOutlineThickness(0);
}

void Piece::moveTo(int _col, int _row)
{
	//std::cout << "Before: " << rect.getPosition().x << ", " << rect.getPosition().y << std::endl;
	
	//rect.setPosition(sf::Vector2f(col * size + size / 2, row * size + size / 2));
	rect.move(sf::Vector2f((_col - col) * size, (_row - row) * size));
	
	col = _col;
	row = _row;
	
	++move;

	//std::cout << "After: " << rect.getPosition().x << ", " << rect.getPosition().y << std::endl;
}

std::vector<sf::Vector2i> Piece::getPossibleMoves(Array2D<Piece*>& _board)
{
	std::vector<sf::Vector2i> _moves;
	return _moves;
}

int Piece::getRow()
{
	return row;
}

int Piece::getCol()
{
	return col;
}

void Piece::setRow(int iRow)
{
	row = iRow;
}

void Piece::setCol(int iCol)
{
	col = iCol;
}

char Piece::getMovementtype()
{
	return movementtype;
}

char Piece::getColour()
{
	return colour;
}

char Piece::getPiece()
{
	return piece;
}

int Piece::getMove()
{
	return move;
}