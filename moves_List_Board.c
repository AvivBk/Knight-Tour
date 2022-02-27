#include"Knight_Tour.h"


/******************* Function prototypes *******************/
void DeallocateDoublyListCell(moveCell* Cell);
void deleteFromMidList(moveCell* prev);
void deleteFromBeginningList(movesList* list);
void deleteFromEndList(movesList* list);
moveCell* findPlaceToDeleteFromList(movesList* list, moveCell* del_cel);
void deleteFromList(movesList* list, moveCell* del_cel);
void calcMove(int* row, int* col, Move node);
void convertToMoveLoc(int* row, int* col, boardPos pos);
void convertToMovePos(int* row, int* col, Move move);
/*********************************************************/



/******************* Function Implementation *******************/


int display(movesList* moves_list, boardPos start, char** board)
{
	moveCell* curr = moves_list->head;
	moveCell* next;
	moveCell* prev = curr;
	Move* first = (Move*)malloc(INIT_SIZE * sizeof(Move));
	int delCount;
	delCount = 0;
	int row, col, tempRow, tempCol;
	char TurnCount = '1';
	row = col = 0;
	while (curr)
	{
		next = curr->next;
		if (curr == moves_list->head) {
			convertToMoveLoc(&row, &col, start);
			setCell(row, col, SIGN, board);
			first->rows = row;
			first->cols = col;
		}
		else
		{
			tempRow = row;
			tempCol = col;
			calcMove(&tempRow, &tempCol, curr->move);

			if (InBounds(tempRow + 1, tempCol + 1) && isEmptyCell(getCell(tempRow + 1, tempCol + 1, board))) {
				setCell(tempRow + 1, tempCol + 1, TurnCount, board);
				row = tempRow;
				col = tempCol;
				TurnCount++;
			}
			else {
				deleteFromList(moves_list, curr);
				delCount++;
			}
		}
		prev = curr;
		curr = next;
	}
	return delCount;
}

void calcMove(int* row, int* col, Move node)
{
	int row1, row2, col1, col2, row3, col3;
	row1 = row2 = col1 = col2 = 0;
	convertToMovePos(&row2, &col2, node);
	*row = (-1) * (*row) + row2;
	*col = (-1) * (*col) + col2;
}


void addToBeginningDoublyList(movesList* list, moveCell* cellToAdd)
{
	if (list->head == NULL)
		list->head = list->tail = cellToAdd;
	else {
		cellToAdd->next = list->head;
		list->head->prev = cellToAdd;
		list->head = cellToAdd;
	}
}

void convertToMoveLoc(int* row, int* col, boardPos pos)
{
	*row = pos[0] - 64;
	*col = pos[1] - 1;
}

void convertToMovePos(int* row, int* col, Move move)
{
	*row = move.rows;
	*col = move.cols;
}

void print_board(char** board) {
	int i, j, t = 0;
	char a[ROWS + 1];
	char row = 'A';
	for (i = 0; i <= ROWS; i++) {
		a[i] = row;
		row++;
	}
	for (i = 0; i <= ROWS; i++) {
		printf("+");

		for (j = 0; j <= COLS; j++)
			printf("---+");
		printf("\n");
		printf("|");

		for (j = 0; j <= COLS; j++)

			if (j == 0 && i > 0)
				printf(" %c |", a[t++]);
			else if (i == 0)
				printf(" %d |", j);
			else
				printf(" %c |", getCell(i, j, board));
		printf("\n");
	}
	printf("+");
	for (j = 0; j <= ROWS; j++)
		printf("---+");
	printf("\n");
}

void addToTail(movesList* list, moveCell* cellToAdd)
{

	if (ListIsEmpty(list))
		list->head = list->tail = cellToAdd;
	else
	{
		cellToAdd->prev = list->tail;
		list->tail->next = cellToAdd;
		list->tail = cellToAdd;
	}
}

void deleteFromMidList(moveCell* prev)
{
	moveCell* DelCel = prev->next;

	prev->next = DelCel->next;
	DelCel->next->prev = prev;
	DeallocateDoublyListCell(DelCel);
}

void deleteFromBeginningList(movesList* list)
{
	list->head = list->head->next;
	if (!list->head) {
		DeallocateDoublyListCell(list->tail);
		list->tail = NULL;
	}
	else
	{
		DeallocateDoublyListCell(list->head->prev);
		list->head->prev = NULL;
	}
}

void deleteFromEndList(movesList* list)
{
	if (list->head == list->tail) {
		DeallocateDoublyListCell(list->tail);
		list->head = list->tail = NULL;
		return;
	}
	list->tail = list->tail->prev;
	DeallocateDoublyListCell(list->tail->next);
	list->tail->next = NULL;
}

moveCell* findPlaceToDeleteFromList(movesList* list, moveCell* del_cel)
{
	moveCell* currCell = list->head;
	moveCell* prevCell = NULL;
	while ((currCell) && (currCell != del_cel)) {
		prevCell = currCell;
		currCell = currCell->next;
	}
	return prevCell;
}

void deleteFromList(movesList* list, moveCell* del_cel)
{
	moveCell* prev;
	if (!list->head) {
		fprintf(stderr, "Allocation error\n");

	}
	else {

		prev = findPlaceToDeleteFromList(list, del_cel);
		if (prev == list->tail) {
			fprintf(stderr, "Allocation error\n");
			return;
		}
		if (!prev)
			deleteFromBeginningList(list);
		else if (prev->next == list->tail)
			deleteFromEndList(list);
		else
			deleteFromMidList(prev);
	}
}

void makeEmptyList(movesList* list)
{
	list->tail = list->head = NULL;
}

bool ListIsEmpty(movesList* list)
{
	if (list->head == NULL)
		return true;
	return false;
}

moveCell* createNewCell(Move moveData, moveCell* prevCell, moveCell* nextCell)
{
	moveCell* newCell = NULL;

	newCell = (moveCell*)malloc(INIT_SIZE * sizeof(moveCell));
	CheckMemoryAllocation(newCell);
	newCell->move.rows = moveData.rows;
	newCell->move.cols = moveData.cols;
	newCell->prev = prevCell;
	newCell->next = nextCell;

	return newCell;
}


void CheckMemoryAllocation(void* ptr)
{
	if (!ptr) {
		fprintf(stderr, "Allocation error\n");
		exit(ERROR);
	}
}
void freeMovesList(movesList* list)
{
	moveCell* currX;
	moveCell* nextX;

	currX = list->head;
	while (currX)
	{
		nextX = currX->next;
		DeallocateDoublyListCell(currX);
		currX = nextX;
	}
}

void DeallocateDoublyListCell(moveCell* Cell)
{
	//free(Cell->move);
	free(Cell);
}
