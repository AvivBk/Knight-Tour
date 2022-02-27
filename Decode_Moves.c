#include"Knight_Tour.h"

/******************* Function prototypes *******************/
static void getDecodedData(BYTE* data, char* decData, movesList* list, int size);
static FILE* openBinFileForReading(char* file);
int countMovesListCell(movesList* list);
/*********************************************************/


/******************* Function Implementation *******************/

int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board)
{
	int i, delCount;
	movesList* list = (movesList*)malloc(INIT_SIZE * sizeof(movesList));
	boardPos start;
	start[0] = 'D'; // check
	start[1] = 3;
	FILE* fpr;
	BYTE tempData[3];	//we read 3 bytes each time
	char DecodeChars[8]; //and we convert them to 8 chars
	fpr = openBinFileForReading(file_name);
	makeEmptyList(list);
	short  movesSize;
	fread(&movesSize, sizeof(short int), 1, fpr);
	for (i = 0; i < movesSize; i += 3)   //we read 3 bytes at a time
	{
		fread(tempData, sizeof(BYTE), 3, fpr);
		if (movesSize - i >= 3)
			getDecodedData(tempData, DecodeChars, list, 3);
		else
			getDecodedData(tempData, DecodeChars, list, movesSize - i);
	}
	delCount = display(list, start, board);
	if (delCount == movesSize - 1) {
		freeMovesList(&list);
		return WORNG_PATH;
	}
	else
		print_board(board);
	if (countEmptyCells(board) == countMovesListCell(&list));
			return FULL_PATH;

	return PARTIAL_PATH;
}

int countMovesListCell(movesList* list)
{
	int count = 0;
	moveCell* curr = list->head;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return count;
}

static FILE* openBinFileForReading(char* file)
{
	FILE* fpw = fopen(file, "rb");
	checkSucceedFileOpen(fpw);
	return fpw;
}

static void getDecodedData(BYTE* data, char* decData, movesList* list, int size)
{
	int i;
	Move* move = (Move*)malloc(INIT_SIZE * sizeof(Move));
	CheckMemoryAllocation(move);
	moveCell* cell;
	BYTE mask1 = 0xE0;	//11100000 
	BYTE mask2 = 0x1C;	//00011100 
	BYTE mask3a = 0x03, mask3b = 0x80;	//0000001110000000
	BYTE mask4 = 0x70;	//01110000  
	BYTE mask5 = 0x0E;	//00001110  
	BYTE mask6a = 0x01, mask6b = 0xC0;	//0000000111000000
	BYTE mask7 = 0x38;	//00111000 
	BYTE mask8 = 0x07;	//00000111	

	for (i = 0; i < size; i++) {
		if (i == 0) {
			move->rows = (data[0] & mask1) >> 5;
			move->cols = (data[0] & mask2) >> 2;
		}
		else if (i == 1) {
			move->rows = ((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7);
			move->cols = decData[3] = (data[1] & mask4) >> 4;
		}
		else if (i == 2) {
			move->rows = (data[1] & mask5) >> 1;
			move->cols = ((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6);
		}
		else {
			move->rows = (data[2] & mask7) >> 3;
			move->cols = data[2] & mask8;
		}
		cell = createNewCell(*move, NULL, NULL);
		addToTail(list, cell);
	}
}

