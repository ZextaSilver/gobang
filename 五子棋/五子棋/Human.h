#pragma once

#include "Chess.h"

class Human
{
private:
	Chess* chess;

public:
	void init(Chess* chess);
	void go();
};

