#include "Knight_Tour.h"


/******************* Function prototypes *******************/
static Move* calcMoveCell(boardPos node1, boardPos node2);
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
static bool findPathCoveringAllBoardAux(treeNode* node, movesList* list, int max);
void convertToMove(int* row, int* col, boardPos pos);
int countEmptyCells(char** board);
/*********************************************************/


/******************* Function Implementation *******************/


movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board)
{
	pathTree tr;
	movesList list;
	bool res;
	makeEmptyList(&list);
	int max = countEmptyCells(board);
	tr = findAllPossiblePaths(start, moves, board);
	res = findPathCoveringAllBoardAux(tr.head, &list, 5);
	freeTree(&tr);
	if (res)
		return &list;
	return NULL;
}

static bool findPathCoveringAllBoardAux(treeNode* node, movesList* list, int max)
{
	moveCell* newCell = NULL;
	int row, col;
	row = col = 0;
	bool res;
	Move* move;
	if (node->next_possible_positions == NULL && max == 0)
		return true;
	else if (node->next_possible_positions == NULL && max != 0)
		return false;

	while (node->next_possible_positions != NULL) {
		res = findPathCoveringAllBoardAux(node->next_possible_positions->node, list, max - 1);
		if (res == true) {
			move = calcMoveCell(&newCell, node->position, node->next_possible_positions->node);
			addToBeginningDoublyList(list, createNewCell(*move, NULL, NULL));
			return true;
		}
		node->next_possible_positions = node->next_possible_positions->next;
	}
	return false;
}

static Move* calcMoveCell(boardPos node1, boardPos node2)
{
	Move* move;
	int row1, row2, col1, col2, row3, col3;
	convertToMove(&row1, &col1, node1);
	convertToMove(&row2, &col2, node2);
	row3 = (-1) * row1 + row2 - 65;
	col3 = (-1) * col1 + col2;
	move = (Move*)malloc(INIT_SIZE * sizeof(Move));
	CheckMemoryAllocation(move);
	move->rows = row3;
	move->cols = col3;
	return move;
}

void convertToMove(int* row, int* col, boardPos pos)
{
	*row = pos[0];
	if ((pos[1] % COLS) != 0)
		*col = (pos[1] % COLS) - 1;
	else
		*col = COLS - 1;
}

int countEmptyCells(char** board)
{
	int j, i, count = 0;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (isEmptyCell(getCell(i + 1, j + 1, board)))
				count++;
		}
	}
	return count;
}
