/*
	1.create, import
	2.design framework
*/

#include <iostream>
#include "ChessGame.h"

using namespace std;

int main()
{
	Human human;
	AI ai;
	Chess chess(13, 46, 44, 67.3);

	ChessGame game(&human, &ai, &chess);


	game.play();
}