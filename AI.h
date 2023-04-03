#pragma once

#include "Chess.h"


class AI
{
private:
	Chess* chess;
	vector<vector<int>> scoreMap;

	void calculateScore();

	ChessPos think();

public:
	void init(Chess* chess);
	void go();
};

