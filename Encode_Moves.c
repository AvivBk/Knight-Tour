#include "Knight_Tour.h"

/******************* Function prototypes *******************/
static void turnOffArrBits(BYTE* arr, BYTE* data, int size);
static FILE* openBinFileForWriting(char* file);
static void convertToboardLocation(unsigned int* row, unsigned int* col, boardPos pos);
static void trunOnBits(BYTE* data, BYTE first, BYTE sec);
/*********************************************************/

/******************* Function Implementation *******************/

static FILE* openBinFileForWriting(char* file)
{
	FILE* fpw = fopen(file, "wb");
	checkSucceedFileOpen(fpw);
	return fpw;
}

void saveListToBinFile(char* file_name, boardPosArray* pos_arr)
{
	FILE* fpr = openBinFileForWriting(file_name);
	unsigned int i, j = 0;
	unsigned int row, col, write = 0;
	row = col = 0;
	short size = pos_arr->size;

	BYTE* enCodeArr = (BYTE*)malloc(SIZE_OF_COMPRESS + 1 * sizeof(BYTE));
	BYTE tempData;
	turnOffArrBits(enCodeArr, &tempData, SIZE_OF_COMPRESS + 1);

	fwrite(&size, sizeof(short), 1, fpr);
	for (i = 0, j = 0; i < pos_arr->size; j++, i++) {
		convertToboardLocation(&row, &col, pos_arr->positions[i]);
		trunOnBits(&tempData, row, col);
		if (j == 0)
			enCodeArr[0] = (enCodeArr[0] | tempData) << 2;
		else if (j == 1) {
			enCodeArr[0] = enCodeArr[0] | (tempData >> 4);
			enCodeArr[1] = enCodeArr[1] | (tempData << 4);
		}
		else if (j == 2) {
			enCodeArr[1] = enCodeArr[1] | (tempData >> 2);
			enCodeArr[2] = enCodeArr[2] | (tempData << 6);
		}
		else {
			enCodeArr[2] = enCodeArr[2] | tempData;
			fwrite(enCodeArr, sizeof(BYTE), SIZE_OF_COMPRESS, fpr);
			turnOffArrBits(enCodeArr, &j, SIZE_OF_COMPRESS + 1);
		}
	}
	while (j > 0 && write < 4) {
		fwrite(&enCodeArr[write++], sizeof(BYTE), 1, fpr);
		j--;
	}
	free(enCodeArr);
	fclose(fpr);
}

static void trunOnBits(BYTE* data, BYTE first, BYTE sec)
{
	*data = 0;
	*data = (first << 3 | sec);
}

static void turnOffArrBits(BYTE* arr, BYTE* data, int size)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = 0;
	*data = 0;
}

static void convertToboardLocation(unsigned int* row, unsigned int* col, boardPos pos)
{
	*row = pos[0] - 65;
	*col = pos[1] - 1;
}

void checkSucceedFileOpen(void* ptr)
{
	if (!ptr) {
		fprintf(stderr, "file openning failed\n");
		exit(ERROR);
	}
}