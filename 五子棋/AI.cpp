#include "AI.h"
#include <time.h>

void AI::calculateScore()
{
	// how many connected chess does human player have
	int personNum = 0;
	// how many connected chess does AI player have
	int aiNum = 0;
	// no chess placed
	int emptyNum = 0;

	// initialize score map values
	for (int i = 0; i < scoreMap.size(); i++)
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getBoardSize();

	// check all the point on the board
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			// if the point has no chess on it
			if (chess->getChessData(row, col))
			{
				continue;
			}


			// check all 8 directions around the current point
			for (int y = -1; y <= 0; y++) // top, middle, bottom
			{
				for (int x = -1; x <= 1; x++) // left, middle, right
				{
					// do not count 0, 0 as the original point
					if (x != 1 && y == 0)
					{
						continue;
					}

					personNum = aiNum = emptyNum = 0;

					// determine what type of advantage black chess is having
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
								 curCol >= 0 && curCol < size &&
								 chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					// 2连
					if (personNum == 1)
					{
						scoreMap[row][col] += 10;
					}
					// 3连
					else if (personNum == 2)
					{
						// 死3
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 30;
						}
						// 活3
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 40;
						}
					}
					// 4连
					else if (personNum == 3)
					{
						// 死4
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 60;
						}
						// 活4
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 5000;
						}
					}
					// 5连
					else if (personNum >= 4)
					{
						scoreMap[row][col] += 20000;
					}

					// determine what type of advantage white chess is having
					emptyNum = 0;

					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
								 curCol >= 0 && curCol < size &&
								 chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					if (aiNum == 0)
					{
						scoreMap[row][col] += 5;
					}
					// 2连
					else if (aiNum == 1)
					{
						scoreMap[row][col] += 10;
					}
					// 3连
					else if (aiNum == 2)
					{
						// 死3
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 25;
						}
						// 活3
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 50;
						}
					}
					// 4连
					else if (aiNum == 3)
					{
						// 死4
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 55;
						}
						// 活4
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 10000;
						}
					}
					// 5连
					else if (aiNum >= 4)
					{
						scoreMap[row][col] += 30000;
					}
				}
			}


		}
	}


}

ChessPos AI::think()
{
	calculateScore();

	int size = chess->getBoardSize();

	int mostValued = 0;
	// vector to store all the points have the same high values
	vector<ChessPos> maxPoints;

	// loop through whole map
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			// if this position is empty
			if (chess->getChessData(row, col) == 0)
			{
				// check which spor worth the most to take the position
				if (scoreMap[row][col] > mostValued)
				{
					mostValued = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				// record all the spot with highest value
				else if (scoreMap[row][col] == mostValued)
				{
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		}
	}

	// decide where to put down the chess randomly
	srand(time(0));
	int index = rand() % maxPoints.size();

	printf("%d\n", index);

	return maxPoints[index];
}

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getBoardSize();

	for (int i = 0; i < size; i++)
	{
		vector<int> row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	// fake stop timer 1 sec
	Sleep(1000);
	chess->chessDown(&pos, CHESS_WHITE);
}
