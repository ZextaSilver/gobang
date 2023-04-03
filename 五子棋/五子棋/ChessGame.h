#pragma once
#include "Human.h"
#include "AI.h"
#include "Chess.h"


class ChessGame
{
private:
	Human* human;
	AI* ai;
	Chess* chess;

public:
	ChessGame(Human* human, AI* ai, Chess* chess);

	void play();
	
};

