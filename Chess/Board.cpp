#include "Board.h"


Board::Board() : selectedPiece(NULL), takeTurns(true)
{
	init();
	cSoundType = NULL;
}

Board::~Board()
{

}

void Board::init()
{
	board.clear();

	// initializes black/white pawns
	for (int _col = 0; _col < COLS; ++_col)
	{
		board[_col][1] = new Pawn(TILE_SIZE, _col, 1, 'b');
		board[_col][6] = new Pawn(TILE_SIZE, _col, 6, 'w');
	}

	// initializes black/white rooks
	board[0][0] = new Rook(TILE_SIZE, 0, 0, 'b');
	board[7][0] = new Rook(TILE_SIZE, 7, 0, 'b');
	board[0][7] = new Rook(TILE_SIZE, 0, 7, 'w');
	board[7][7] = new Rook(TILE_SIZE, 7, 7, 'w');

	// initializes black/white knights
	board[1][0] = new Knight(TILE_SIZE, 1, 0, 'b');
	board[6][0] = new Knight(TILE_SIZE, 6, 0, 'b');
	board[1][7] = new Knight(TILE_SIZE, 1, 7, 'w');
	board[6][7] = new Knight(TILE_SIZE, 6, 7, 'w');

	// initializes black/white bishops
	board[2][0] = new Bishop(TILE_SIZE, 2, 0, 'b');
	board[5][0] = new Bishop(TILE_SIZE, 5, 0, 'b');
	board[2][7] = new Bishop(TILE_SIZE, 2, 7, 'w');
	board[5][7] = new Bishop(TILE_SIZE, 5, 7, 'w');

	// initializes black/white queen
	board[3][0] = new Queen(TILE_SIZE, 3, 0, 'b');
	board[3][7] = new Queen(TILE_SIZE, 3, 7, 'w');

	// initializes black/white king
	board[4][0] = new King(TILE_SIZE, 4, 0, 'b');
	board[4][7] = new King(TILE_SIZE, 4, 7, 'w');

	curPlayer = PLAYER_ONE;


}

void Board::update()
{
	
}

void Board::render(Window* _window)
{
	// renders the checkered board
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			sf::RectangleShape _rect;
			_rect.setOrigin(0, 0);
			_rect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			_rect.setPosition(sf::Vector2f(_col * TILE_SIZE, _row * TILE_SIZE));
			
			// decides if a square should be white or gray
			if ((_row + _col) % 2 == 0) _rect.setFillColor(sf::Color::White);
			else _rect.setFillColor(sf::Color(192, 192, 192));

			_window->render(_rect);
		}
	}

	// renders the possible moves (if any)
	for (auto _it = possibleMoves.begin(); _it != possibleMoves.end(); ++_it)
	{
		sf::Vector2i _move = *_it;
		sf::RectangleShape _rect(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		
		_rect.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
		_rect.setPosition(sf::Vector2f(_move.x * TILE_SIZE + TILE_SIZE / 2, _move.y * TILE_SIZE + TILE_SIZE / 2));
		_rect.setScale(sf::Vector2f(0.96, 0.96));
		_rect.setOutlineColor(sf::Color::Yellow);
		_rect.setOutlineThickness(3);

		if ((_move.x + _move.y) % 2 == 0) _rect.setFillColor(sf::Color::White);
		else _rect.setFillColor(sf::Color(192, 192, 192));

		_window->render(_rect);
	}

	// renders the pieces
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			if (board[_col][_row])
			{
				//std::cout << "Rendering piece at: " << board[_col][_row]->getCol() << ", " << board[_col][_row]->getRow() << "(" << _col << ", " << _row << ")" << std::endl;
				board[_col][_row]->render(_window);
			}
		}
	}
}

void Board::mouseClicked(sf::Vector2i _position)
{
	resetBoard();

	int _row = (int)floor(_position.y / TILE_SIZE);
	int _col = (int)floor(_position.x / TILE_SIZE);

	if (_col >= COLS) return;

	// NUSRET 
	// Not focused when clicked the antoher piece of he current player
	//
	if (possibleMoves.size() != 0 )
		checkPossibleMoves(_col, _row);
	//


	if (board[_col][_row]  /* && possibleMoves.size() == 0*/)
	{
		if (!takeTurns || board[_col][_row]->getColour() == curPlayer)
		{
			selectedPiece = board[_col][_row];

			if (isCheck)
			{
				GetPossibleBlockCheck();

				if (selectedPiece->getPiece() == 'K')
				{
					sf::Vector2i possiblemove;

					possibleMoves = selectedPiece->getPossibleMoves(board);

					ControlAnyCheckPosition();

					for (auto _it = possibleMoves.begin(); _it != possibleMoves.end(); ++_it)
					{
						possiblemove = *_it;
						if ((std::find(PossibleMovesForBlockCheck.begin(), PossibleMovesForBlockCheck.end(), possiblemove) != PossibleMovesForBlockCheck.end()))
						{
							if (!(board[possiblemove.x][possiblemove.y]))
								possibleMoves.erase(_it);
							break;
						}
					}
				}

				else if (PossibleMovesForBlockCheck.size() == 0)
				{
					selectedPiece->reset();
					possibleMoves.clear();
					return;
				}
				else
				{
					possibleMoves = PossibleMovesForBlockCheck;
				}
			}
			else
			{
				possibleMoves = selectedPiece->getPossibleMoves(board);
				ControlAnyCheckPosition();
			}
			selectedPiece->mouseClicked();
		}
		/// <summary>
		/// NUSRET 
		/// selected piece must be reset
		/// </summary>
		/// <param name="_position"></param>
		else if (selectedPiece != NULL)
		{
			selectedPiece->reset();
			possibleMoves.clear();
		}
	}
}

void Board::checkPossibleMoves(int _col, int _row)
{
	//
	//Nusret
	sf::Vector2i _move;
	//

	for (auto _it = possibleMoves.begin(); _it != possibleMoves.end(); ++_it)
	{
		_move = *_it;

		if (_move.x == _col && _move.y == _row)
		{

			if (board[_col][_row] && board[_col][_row]->getPiece() == 'K')
			{
				init();
				break;
			}
			//


			if (board[_col][_row] && board[_col][_row]->getColour() == selectedPiece->getColour())
			{
				Piece* _piece = board[_col][_row];
				board[selectedPiece->getCol()][selectedPiece->getRow()] = _piece;
				_piece->moveTo(selectedPiece->getCol(), selectedPiece->getRow());
			}
			else
				board[selectedPiece->getCol()][selectedPiece->getRow()] = NULL;


			selectedPiece->moveTo(_col, _row);

			cSoundType = board[_col][_row] ? sound.PIECE_KILL : sound.PIECE_MOVE;

			board[_col][_row] = selectedPiece;

			possibleMoves = selectedPiece->getPossibleMoves(board);

			if (IsCheckState(selectedPiece, possibleMoves, curPlayer))
			{
				killerPiece = selectedPiece;
				killerPossibleMoves = possibleMoves;
				SavePotentiallyCheckPosition();

			}

			CheckHeroPawnAndMakeQueen();

			sound.Play_Sound(isCheck ? sound.PIECE_CHECK : cSoundType);

			curPlayer = curPlayer == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE;

			printf("moved row : %d moved col : %d\n", _move.y, _move.x);

			break;
		}
	}

	selectedPiece = NULL;
	possibleMoves.clear();
}

void Board::CheckHeroPawnAndMakeQueen()
{
	
	if (selectedPiece->getPiece() == 'p')
	{
		if (selectedPiece->getColour() == 'w' && selectedPiece->getRow() == 0)
			board[selectedPiece->getCol()][selectedPiece->getRow()] = new Queen(TILE_SIZE, selectedPiece->getCol(), selectedPiece->getRow(), 'w');

		else if (selectedPiece->getColour() == 'b' && selectedPiece->getRow() == 7)
			board[selectedPiece->getCol()][selectedPiece->getRow()] = new Queen(TILE_SIZE, selectedPiece->getCol(), selectedPiece->getRow(), 'b');


	}
}


// is current player's piece allow playing ?
void Board::ControlAnyCheckPosition()
{
	sf::Vector2i possiblemove;

	const char _orjrow = selectedPiece->getRow(); // implicit cast
	const char _orjcol = selectedPiece->getCol(); // implicit cast

	char tempPiecerow = _orjrow;
	char tempPiececol = _orjcol;

	char oppositePlayer = curPlayer == PLAYER_ONE ? PLAYER_TWO : PLAYER_ONE;

	Piece* temppiece = NULL;
	bool eraseflag = false;

	for (auto _iter = possibleMoves.begin(); _iter != possibleMoves.end();)
	{
		possiblemove = *_iter;
		
		temppiece = board[possiblemove.x][possiblemove.y];
		board[possiblemove.x][possiblemove.y] = selectedPiece;
		board[_orjcol][_orjrow] = NULL;
		eraseflag = false;

		for (char _row = 0; (_row < ROWS) && !eraseflag; ++_row)
		{
			for (char _col = 0; _col < COLS; ++_col)
			{
				if (board[_col][_row] && board[_col][_row]->getColour() == oppositePlayer)
				{	
					if (IsCheckState(board[_col][_row], board[_col][_row]->getPossibleMoves(board), oppositePlayer))
					{
						_iter = possibleMoves.erase(_iter);
						eraseflag = true;
						break;
					}

				}
			}

		}

		board[_orjcol][_orjrow] = selectedPiece;
		board[possiblemove.x][possiblemove.y] = temppiece;

		if (!eraseflag)_iter++; // Erase function is increase iterator

	}
	isCheck = false;

}

// Get the playing piece move type: cross or flat
char Board::GetChecktype()
{
	char movementType = killerPiece->getMovementtype();
	
	if (movementType == 3) // if killer is queen
		movementType = (killerPiece->getCol() == kingcurcol || killerPiece->getRow() == kingcurrow) ? 2 : 1;
		
	return movementType;
}

void Board::SavePotentiallyCheckPosition()
{
	int ipotcheckpos(0);

	sf::Vector2i possiblemove, templatepossiblemove;
	std::vector<sf::Vector2i> templatepossibleMoves;

	const char _orjrow = killerPiece->getRow();
	const char _orjcol = killerPiece->getCol();

	char killerPiecerow = _orjrow;
	char killerPiececol = _orjcol;

	char movementType = GetChecktype();

	PotentiallyCheckMoves.clear();

	switch (movementType)
	{
	case 1:
		while (killerPiececol != kingcurcol)
		{
			possiblemove.x = killerPiececol < kingcurcol ? killerPiececol++ : killerPiececol--;
			possiblemove.y = killerPiecerow < kingcurrow ? killerPiecerow++ : killerPiecerow--;

			PotentiallyCheckMoves.push_back(possiblemove);
		}
			
	break;
	case 2:
		while (killerPiececol != kingcurcol || killerPiecerow != kingcurrow)
		{
			if (killerPiececol == kingcurcol)
			{
				possiblemove.y = killerPiecerow > kingcurrow ? killerPiecerow-- : killerPiecerow++;
				possiblemove.x = killerPiececol;
			}
			else
			{
				possiblemove.x = killerPiececol > kingcurcol ? killerPiececol-- : killerPiececol++;			
				possiblemove.y = killerPiecerow;
			}

			PotentiallyCheckMoves.push_back(possiblemove);
		}
	break;
		case 3:
			break;
		default:
			break;
	}

	killerPiece->setRow(_orjrow);

	killerPiece->setCol(_orjcol);
}


bool Board::IsCheckState(Piece* Piece, std::vector<sf::Vector2i> posMoves,char playercolour)
{
	isCheck = false;
	//if (!isCheck)
	//{
		sf::Vector2i possiblemove;
		//
		//the last position of the last selected piece 

		for (auto _it = posMoves.begin(); _it != posMoves.end(); ++_it)
		{
			possiblemove = *_it;

			if (board[possiblemove.x][possiblemove.y])
				if (board[possiblemove.x][possiblemove.y]->getColour() != playercolour && board[possiblemove.x][possiblemove.y]->getPiece() == 'K')
				{
					kingcurcol = possiblemove.x;
					kingcurrow = possiblemove.y;
					isCheck = true;
					break;
				}
		}
	//}
	
	return isCheck;
}
void Board::GetPossibleBlockCheck()
{

	isPossibleBlockCheck = false;
	PossibleMovesForBlockCheck.clear();

	if (isCheck)
	{
		sf::Vector2i possiblemove;
		possibleMoves = selectedPiece->getPossibleMoves(board);

		for (auto _it = possibleMoves.begin(); _it != possibleMoves.end(); ++_it)
		{
			possiblemove = *_it;

			if (board[selectedPiece->getCol()][selectedPiece->getRow()])
			{
				if (/*board[selectedPiece->getCol()][selectedPiece->getRow()]->getColour() != curPlayer
					&& */(board[possiblemove.x][possiblemove.y] == killerPiece 
						|| (std::find(PotentiallyCheckMoves.begin(), PotentiallyCheckMoves.end(), possiblemove) != PotentiallyCheckMoves.end())
						)
					)
				{
					PossibleMovesForBlockCheck.push_back(possiblemove);
					isPossibleBlockCheck = true;
					//break;
				}
			}
		}
	}

}

void Board::resetBoard()
{
	// resets each of the piece's selected values every time the mouse is clicked
	for (int _row = 0; _row < ROWS; ++_row)
	{
		for (int _col = 0; _col < COLS; ++_col)
		{
			if(board[_col][_row]) board[_col][_row]->reset();
		}
	}
}

int Board::getCols()
{
	return COLS;
}

int Board::getRows()
{
	return ROWS;
}

int Board::getTileSize()
{
	return TILE_SIZE;
}

void Board::switchTakeTurns()
{
	takeTurns = !takeTurns;
}
