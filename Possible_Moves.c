#include "Knight_Tour.h"

/******************* Function prototypes *******************/
static boardPosArray* createBoardPosArr(movesArray** moves, int location);
static void updateMove(Move* dest, Move* src, int* size);
static void removeWorngMove(movesArray** movesArr, int loc, char** board);
static void reallocationTemp(Move* src, int size, movesArray** moves);
/*********************************************************/

/******************* Function Implementation *******************/

boardPosArray** validMoves(movesArray** moves, char** board)
{
	unsigned int i, size;
	size = ROWS * COLS;
	boardPosArray** PosArray = (boardPosArray**)malloc(ROWS * COLS * sizeof(boardPosArray));
	CheckMemoryAllocation(PosArray);
	for (i = 0; i < size; i++)
		removeWorngMove(&moves[i], i, board);

	for (i = 0; i < ROWS * COLS; i++)
		PosArray[i] = createBoardPosArr(&moves[i], i);

	return PosArray;
}

void removeWorngMove(movesArray** movesArr, int loc, char** board)
{
	Move* tempMoves;
	int logSize, row, col, i;
	logSize = 0;
	if ((*movesArr)->size == 0)
		return;
	tempMoves = (Move*)malloc((*movesArr)->size * sizeof(Move));
	CheckMemoryAllocation(tempMoves);

	for (i = 0; i < (*movesArr)->size; i++)
	{
		row = (loc / COLS) + (*movesArr)->moves[i].rows;
		col = (loc % COLS) + (*movesArr)->moves[i].cols;
		if (InBounds(row, col) && (isEmptyCell(getCell(row + 1, col + 1, board)))) {
			tempMoves[logSize].rows = (*movesArr)->moves[i].rows;
			tempMoves[logSize++].cols = (*movesArr)->moves[i].cols;
		}
	}
	reallocationTemp(tempMoves, logSize, movesArr);
}

static void updateMove(Move* dest, Move* src, int* size)
{
	dest->rows = src->rows;
	dest->cols = src->cols;
	*size = *size + 1;
}

static void  reallocationTemp(Move* src, int size, movesArray** moves)
{
	free((*moves)->moves);
	(*moves)->size = size;
	(*moves)->moves = src;
}

static boardPosArray* createBoardPosArr(movesArray** moves, int location)
{
	char row, col;
	int i;
	boardPosArray* PosArr = (boardPosArray*)malloc(INIT_SIZE * sizeof(boardPosArray));
	CheckMemoryAllocation(PosArr);
	PosArr->size = (*moves)->size;
	PosArr->positions = (boardPos*)malloc(PosArr->size * sizeof(boardPos));
	CheckMemoryAllocation(PosArr->positions);

	row = location / COLS + 65;
	col = (location % COLS) + 1;

	for (i = 0; i < PosArr->size; i++) {
		PosArr->positions[i][0] = row + (*moves)->moves[i].rows;
		PosArr->positions[i][1] = col + (*moves)->moves[i].cols;
	}
	return PosArr;
}


bool isEmptyCell(char ch)
{
	if (ch == ' ')//CHECK
		return true;
	return false;
}

bool InBounds(int row, int col)
{
	if (row < ROWS && row > 0 && col < COLS && col > 0)
		return true;
	return false;
}


char getCell(int row, int col, char** board)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign, char** board)
{
	board[row - 1][col - 1] = sign;
}

char** init_board(void) 
{
	char** board;
	int i, j;
	board = (char**)malloc(ROWS * sizeof(char*));
	CheckMemoryAllocation(board);

	for (i = 0; i < ROWS; i++) {
		board[i] = (char*)malloc(COLS * sizeof(char));
		CheckMemoryAllocation(board[i]);
		for (j = 0; j < COLS; j++)
			board[i][j] = '  ';
	}
	return board;
}







