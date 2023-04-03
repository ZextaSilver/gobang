#include "Human.h"

void Human::init(Chess* chess)
{
	this->chess = chess;
}

void Human::go()
{
	MOUSEMSG msg;
	ChessPos pos;

	while (1)
	{
		// get mouse input
		msg = GetMouseMsg();

		// determine if click position is in a valid range
		if (msg.uMsg == WM_LBUTTONDOWN && chess->validClickPos(msg.x, msg.y, &pos))
		{
			break;
		}
	}

	//printf("%d, %d\n", pos.row, pos.col);

	chess->chessDown(&pos, CHESS_BLACK);
}
