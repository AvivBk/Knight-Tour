#include "Knight_Tour.h"


/*******************  Function Prototypes *******************/
static void findAllPossiblePathsAux(treeNode* head, boardPosArray** boardPosArr, TrackList* trace);
static void makeEmptyList(pathTree* list);
static treeNode* createNewTNode(boardPos data, treeNodeListCell* list);
static treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* nextCell);
static trackListCell* createTrackListCell(treeNode* pos, trackListCell* next);
static void addToEndOfList(treeNodeListCell** head, treeNode* node);
static bool isCellAlreadyBeenVisited(TrackList* list, boardPos currPos);
static void convertToboardLoc(int* row, int* col, boardPos pos);
static void freeList(treeNode* list);
static void printTreeAux(treeNode* node, int level);
static void freeTraceList(TrackList* list);
static void insertToEndTrackList(TrackList* list, treeNode* pos);
static void addToTrackTail(TrackList* list, trackListCell* cellToAdd);
static void deleteFromEndTrackList(TrackList* list);
static bool TrackListIsEmpty(TrackList* list);
/*********************************************************/


/******************* Function Implementation *******************/

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board)
{
	pathTree path;
	TrackList* traceList = (TrackList*)malloc(INIT_SIZE * sizeof(TrackList));
	boardPosArray** boardPosArr;
	int size = ROWS * COLS;
	boardPosArr = (boardPosArray**)malloc(size * sizeof(boardPosArray*));
	CheckMemoryAllocation(boardPosArr);
	boardPosArr = validMoves(moves, board);

	path.head = createNewTNode(start, NULL);
	traceList->head = createTrackListCell(path.head, NULL);
	traceList->tail = traceList->head;
	findAllPossiblePathsAux(path.head, boardPosArr, traceList);
	freeTraceList(traceList);
	return path;
}

static void findAllPossiblePathsAux(treeNode* head, boardPosArray** boardPosArr, TrackList* trace)
{
	boardPos* positions;
	treeNode* curr;
	int row, col, posSize, i;
	row = col = 0;
	convertToboardLoc(&row, &col, head->position);
	positions = boardPosArr[row + col]->positions;
	posSize = boardPosArr[row + col]->size;

	if (posSize == 0)
		return;

	for (i = 0; i < posSize; i++) {
		curr = createNewTNode(&positions[i], NULL);
		CheckMemoryAllocation(curr);
		if (!isCellAlreadyBeenVisited(trace, positions[i])) {
			addToEndOfList(&head->next_possible_positions, curr);
			insertToEndTrackList(trace, curr);
			findAllPossiblePathsAux(curr, boardPosArr, trace);
			deleteFromEndTrackList(trace);
		}
		else
			free(curr);
	}
}

static bool isCellAlreadyBeenVisited(TrackList* list, boardPos currPos)
{
	trackListCell* curr = list->head;
	while (curr)
	{
		if (curr->position[0] == currPos[0] && curr->position[1] == currPos[1])
			return true;
		curr = curr->next;
	}
	return false;
}

void convertToboardLoc(int* row, int* col, boardPos pos)
{
	*row = (pos[0] - 65) * COLS;
	if ((pos[1] % COLS) != 0)
		*col = (pos[1] % COLS) - 1;
	else
		*col = COLS - 1;
}

static void makeEmptyList(pathTree* list)
{
	list->head = NULL;
}

static void addToEndOfList(treeNodeListCell** head, treeNode* node)
{
	treeNodeListCell* curr = *head;
	treeNodeListCell* prev = NULL;
	if (curr) {
		while (curr->next)
			curr = curr->next;
		curr->next = createNewListCell(node, NULL);
		CheckMemoryAllocation(curr->next);
	}
	else {
		curr = createNewListCell(node, NULL);
		CheckMemoryAllocation(curr);
		*head = curr;
	}
}

static treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* nextCell)
{
	treeNodeListCell* newCell;
	newCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	CheckMemoryAllocation(newCell);
	newCell->node = node;
	newCell->next = nextCell;

	return newCell;
}


static trackListCell* createTrackListCell(treeNode* pos, trackListCell* next)
{
	trackListCell* newCell = NULL;
	newCell = (trackListCell*)malloc(sizeof(trackListCell));
	CheckMemoryAllocation(newCell);
	newCell->position[0] = pos->position[0];
	newCell->position[1] = pos->position[1];
	newCell->next = next;

	return newCell;
}

static void insertToEndTrackList(TrackList* list, treeNode* pos)
{
	trackListCell* newTail = createTrackListCell(pos, NULL);
	addToTrackTail(list, newTail);
}


static treeNode* createNewTNode(boardPos data, treeNodeListCell* list)
{
	treeNode* res;
	res = (treeNode*)malloc(sizeof(treeNode));
	CheckMemoryAllocation(res);
	res->position[0] = data[0];
	res->position[1] = data[1];
	res->next_possible_positions = list;
	return res;
}

/* free all memory of a tree */
void freeTree(pathTree* tr)
{
	freeList(tr->head);
}

static void freeTraceList(TrackList* list)
{
	trackListCell* curr = list->head;
	trackListCell* next = NULL;
	while (curr)
	{
		next = curr->next;
		free(curr->position);
		curr = next;
	}
}

static void freeList(treeNode* root)
{
	treeNodeListCell* curr = root->next_possible_positions;
	treeNodeListCell* next;

	while (curr)
	{
		next = curr->next;
		free(curr->node);
		free(curr);
		curr = next;
	}
	root->next_possible_positions = NULL;
}// need to add free list func


void printTree(pathTree tree)
{
	printTreeAux(tree.head, 0);
}

static void printTreeAux(treeNode* node, int level)
{
	int i;
	treeNodeListCell* curr = node->next_possible_positions;
	if (!(curr))
	{
		for (i = 0; i < level; i++)
		{
			printf(" ");
		}
		printf("L%d: %c%d leaf\n", level, node->position[0], node->position[1]);
	}
	else
	{
		for (i = 0; i < level; i++)
		{
			printf(" ");
		}
		printf("L%d: %c%d\n", level, node->position[0], node->position[1]);
		while (curr)
		{
			printTreeAux(curr->node, level + 1);
			curr = curr->next;
		}
	}
}

static void addToTrackTail(TrackList* list, trackListCell* cellToAdd)
{

	if (TrackListIsEmpty(list))
		list->head = list->tail = cellToAdd;
	else
	{
		list->tail->next = cellToAdd;
		list->tail = cellToAdd;
	}
}

static bool TrackListIsEmpty(TrackList* list)
{
	if (list->head == NULL)
		return true;
	return false;
}

static void deleteFromEndTrackList(TrackList* list)
{
	trackListCell* head, * prev;
	head = list->head;
	prev = head;
	if (TrackListIsEmpty(list))
		return;
	while (head->next != NULL)
	{
		prev = head;
		head = head->next;
	}
	free(prev->next);
	list->tail = prev;
	prev->next = NULL;
}