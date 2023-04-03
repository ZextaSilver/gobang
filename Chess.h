#pragma once
#include <graphics.h>
#include <vector>

using namespace std;

struct ChessPos
{
	int row;
	int col;

	ChessPos(int r = 0, int c = 0) : row(r), col(c) {};
};

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chessColor;

class Chess
{
private:
	// chess image
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;
	// size of the board
	int gradeSize;
	// board margin size
	int marginX, marginY;
	float chessSize;

	// use to store current chess placement, 0: empty, 1: black, -1: white
	vector<vector<int>> chessMap;

	// determine whos turn to play, true: black, false: white
	bool playerFlag;

	void updateGameMap(ChessPos* pos);

	bool checkWin();

	ChessPos lastPos;

public:

	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	// init chess board, load picture and sound resources
	void init();

	// determine mouse click position is a valid placement or not,
	// if so, then store the x, y coordinate into chess's position
	bool validClickPos(int x, int y, ChessPos* pos);

	// place the chess at (pos), with (color)
	void chessDown(ChessPos* pos, chessColor color);

	// see what type of board does user want
	int  getBoardSize(); //13, 15, 17, 19 lines chess board

	// getter function
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	// determine if game is finished
	bool isGameOver();

};

