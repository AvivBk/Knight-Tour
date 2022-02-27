#ifndef structure_and_defines_H
#define structure_and_defines_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/***** DEFINES *****/
#define ROWS 5
#define COLS 5
#define SIGN '#'
#define ERROR -1
#define INIT_SIZE 1
#define SIZE_OF_COMPRESS 3
#define WORNG_PATH 1
#define  FULL_PATH 2
#define PARTIAL_PATH 3

char board[ROWS][COLS];

typedef unsigned char BYTE;
typedef char boardPos[2];


/*****  data structures *****/
typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move* moves;
} movesArray;

typedef struct _moveCell {
	Move move;
	struct _moveCell* next, * prev;
} moveCell;

typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos* positions;
} boardPosArray;

typedef struct _trackListCell {
	boardPos position;
	struct _trackListCell* next;
}trackListCell;

typedef struct _trackList {
	trackListCell* head;
	trackListCell* tail;
}TrackList;

/***** Path tree by Singly linked list  *****/

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell* next_possible_positions; 
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree {
	treeNode* head;
} pathTree;

#endif