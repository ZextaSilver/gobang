#include "ChessGame.h"


ChessGame::ChessGame(Human* human, AI* ai, Chess* chess)
{
	this->human = human;
	this->ai = ai;
	this->chess = chess;

	human->init(chess);
	ai->init(chess);
}

// match start
void ChessGame::play()
{

	chess->init();

	while (1)
	{
		human->go();
		if (chess->isGameOver())
		{
			chess->init();
			continue;
		}

		ai->go();
		if (chess->isGameOver())
		{
			chess->init();
			continue;
		}
	}



}
