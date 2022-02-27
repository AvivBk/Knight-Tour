#ifndef Knight_Tour_H
#define Knight_Tour_H

#include"structure_and_defines.h"

//* 311452510 *//
//* aviv barkai *//


/*******************  Public Function Prototypes *******************/
boardPosArray** validMoves(movesArray** moves, char** board);
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
int display(movesList* moves_list, boardPos start, char** board);
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);


char** init_board(void);
void convertToboardLocation(unsigned int* row, unsigned int* col, boardPos pos);
char getCell(int row, int col, char** board);
void setCell(int row, int col, char sign, char** board);
int countEmptyCells(char** board);
void convertToMove(int* row, int* col, boardPos pos);
bool InBounds(int row, int col);
bool isEmptyCell(char ch);
void convertToboardLoc(int* row, int* col, boardPos pos);

bool ListIsEmpty(movesList* list);
void makeEmptyList(movesList* list);
void addToBeginningDoublyList(movesList* list, moveCell* cellToAdd);
moveCell* createNewCell(Move moveData, moveCell* prevCell, moveCell* nextCell);
void addToTail(movesList* list, moveCell* cellToAdd);
void DeallocateDoublyListCell(moveCell* xCell);

void CheckMemoryAllocation(void* ptr);
void checkSucceedFileOpen(void* ptr);
void freeMovesList(movesList* list);
void freeTree(pathTree* list);


#endif
