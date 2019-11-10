// Thomas Evon
// CS 330
// CS330HW10Functions.h
// header file that contains all functions used for CS330HW10.c

#ifndef CS330HW10GFUNCTIONS_H
#define CS330HW10GFUNCTIONS_H

#include"CS330HW10Globals.h"

// accessor prototypes:

// updators
void updateL1();
void updateTLB();
void updateL2();

// accessors
void disk_access();
void PT_Lookup();
void buf_access();
void L2_Access();
void TLB_Access();
void L1I_Access();
void L1D_Access();

//------------------------------------------------------------------------
// Utility Functions:

// displays array
void displayArray(int count) {
	for (int r = 0; r < count; r++){
		// printf("%s %u \n", "page: ", BUFArr[r].page);
		printf("%s %d \n", "v: ", BUFArr[r].v);
		printf("%s %d \n", "d: ", BUFArr[r].d);
	}
}

// discovers the least-recently used L2 cache
void L2LRU() {
	int sort[4];
	sort[0] = L2ArrA[0].used;
	sort[1] = L2ArrB[0].used;
	sort[2] = L2ArrC[0].used;
	sort[3] = L2ArrD[0].used;

	int max;
	int i = 0;
	int j = i + 1;
	for (i; i < 3; i++) {
		if (sort[i] > sort[j])
			max = sort[i];
		else max = sort[j];
		j++;
	}
	if (max == L2ArrA[0].used) L2_LRU = 'a';
	else if (max == L2ArrB[0].used) L2_LRU = 'b';
	else if (max == L2ArrC[0].used) L2_LRU = 'c';
	else if (max == L2ArrD[0].used) L2_LRU = 'd';
}


// initates all arrays to be empty
void init_arrays() {
	// initialize arrays:
	for (int a = 0; a < L1SIZE; a++) {
		L1IArr[a].v = 0;
		L1IArr[a].d = 0;
		L1IArr[a].page = 0;
	}

	for (int b = 0; b < L1SIZE; b++) {
		L1DArr[b].v = 0;
		L1DArr[b].d = 0;
		L1DArr[b].page = 0;
	}

	for (int c = 0; c < L2SIZE; c++) {
		L2ArrA[c].v = 0;
		L2ArrA[c].d = 0;
		L2ArrA[c].frame = 0;
		L2ArrA[c].used = 0;
	}

	for (int c1 = 0; c1 < L2SIZE; c1++) {
		L2ArrB[c1].v = 0;
		L2ArrB[c1].d = 0;
		L2ArrB[c1].frame = 0;
		L2ArrB[c1].used = 0;
	}

	for (int c2 = 0; c2 < L2SIZE; c2++) {
		L2ArrC[c2].v = 0;
		L2ArrC[c2].d = 0;
		L2ArrC[c2].frame = 0;
		L2ArrC[c2].used = 0;
	}

	for (int c3 = 0; c3 < L2SIZE; c3++) {
		L2ArrD[c3].v = 0;
		L2ArrD[c3].d = 0;
		L2ArrD[c3].frame = 0;
		L2ArrD[c3].used = 0;
	}

	for (int d = 0; d < TLBSIZE; d++) {
		TLBArr[d].v = 0;
		TLBArr[d].page = 0;
		TLBArr[d].frame = 0;
	}

	for (int e = 0; e < PTSIZE; e++) {
		PTArr[e].v = 0;
		PTArr[e].d = 0;
		PTArr[e].frame = 0;
	}

	for (int f = 0; f < FTSIZE; f++) {
		FTArr[f].frame = 0;
	}

	for (int g = 0; g < BUFSIZE; g++) {
		BUFArr[g].v = 0;
		BUFArr[g].d = 0;
		BUFArr[g].frame = 0;
	}
}


// converts a str to an integer
int convertToInt(char* inChar) {
	int returnInt = atoi(inChar);
	return returnInt;
}


// strips out a desired section of a string
char* stripString(char* inStr, int lower, int upper) {
	inStr[upper];
	strncpy(inStr, inStr+lower, upper);
	inStr[upper] = '\0';

	return inStr;
}


// returns a decimal value for virtual OFFSET
unsigned int returnOffset(unsigned int decimalAddress) {
	unsigned int mask = 4095; /* 0xFFF */
	unsigned int extract = mask & decimalAddress;
	return extract;
}


// cleans text file lines of spaces and commas
char* scrubFileLine(char* str) {
	int count, j;
    	for (int i = count = 0; str[i]; i++)
		if (str[i] != ' ')
			str[count++] = str[i]; // remove space
	str[count] = '\0';

    	for (int i = j = 0; str[i]; i++)
       		if (str[i] != ',')
          		str[j++] = str[i]; // remove comma

	str[j] = '\0';

	return str;
}


// returns a decimal value for virtual PAGENUMBER
unsigned int returnPageNumber(unsigned int decimalAddress) {
	unsigned int mask = 4294963200; /* 0xFFFFF000 */
	unsigned int extract = mask & decimalAddress;
	extract = extract >> 12;
	return extract;
}


// converts a string to an unsigned int
unsigned int convert(char *str) {
   	// reference pointer
    	char* end;
    	unsigned long result; //strtoul returns long int type

    	// integer with base 16 for hex
    	result = strtoul(str, &end, 16);
	unsigned int output = result; // long -> int
	return output;
}


// function to convert decimal to binary
void displayBinary(unsigned int n)
{
    // array to store binary number
    int binaryNum[32];

	int i = 31;
	// Size of an integer is assumed to be 32 bits
    for (i; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            binaryNum[i] = 1;
        else
            binaryNum[i] = 0;
    }

    // printing binary array in reverse order
    for (int j = 31; j >= 0; j--)
        printf("%d", binaryNum[j]);

	printf("\n");
}


//------------------------------------------------------------------------
// accessor Functions:

void L1I_Access() {
	CLOCKS += 4;
	L1IACCESSES++;
	unsigned int index = ca.L1Index; // ca.va[12-4]
	if (L1IArr[index].page == ca.pn && L1IArr[index].v == 1) { // hit
		L1IHITS++;
		L1IArr[index].d = 1; // set dirty
		if (TESTFLOW == 1) printf("L1Ihit\n");
	}
	else { // miss
		TLB_Access();
		if (TESTFLOW == 1) printf("L1I miss\n");
	}
	return;
}


void L1D_Access() {
	CLOCKS += 4;
	L1DACCESSES++;
	unsigned int index = ca.L1Index; // ca.va[12-4]
	if (L1DArr[index].page == ca.pn && L1DArr[index].v == 1) // hit
		L1DHITS++;
		L1DArr[index].d = 1; // set dirty
		if (TESTFLOW == 1) printf("L1D hit\n");
	else { // miss
		TLB_Access();
		if (TESTFLOW == 1) printf("L1D miss\n");
	}
	return;
}


void TLB_Access() {
	// TLB doesn't cost any clocks
	TLBACCESSES++;
	unsigned int index = TLBPTR;
	if (TLBArr[index].frame = ca.fn && TLBArr[index].v == 1) { // hit
		TLBHITS++;
		updateL1(); // update the appropriate L1 cache

		// generate pa and fn and store into ca:

		// update the L2 cache using LRU:


		if (TESTFLOW == 1) printf("TLB hit\n");
	}
	else { // miss
		PT_Lookup();
		if (TESTFLOW == 1) printf("TLB miss\n");
	}
	return;
}


void buf_access() {
	CLOCKS += 200;
	BUFACCESSES++;
	unsigned int index = ca.pn & 15; // 12 = 0xF mask for rightmost 4 bits
	if (BUFArr[index].frame == ca.fn) { // hit
		// update PT
		// update L2
		// update TLB
		// update L1


		if (TESTFLOW == 1) printf("buffer hit\n");
	}
	else { // miss
		// disk_Access();
		if (TESTFLOW == 1) printf("buffer miss\n");
		disk_access();
	}
	return;
}


void PT_Lookup() {
	CLOCKS += 50;
	unsigned int index = ca.PTIndex;
	if (PTArr[index].v == 1) { // hit
		// update the L2 cache using LRU:
		L2LRU(); // sets global to correct LRU L2 cache
		// if (L2_LRU == 'a')
		// update TLB:
		// update appropriate L1cache:
		if (TESTFLOW == 1) printf("PT hit\n");
	}
	else { // miss
		PAGEFAULTS++;
		// buf_access();
		if (TESTFLOW == 1) printf("Page Fault\n");
		buf_access();
	}
	return;
}

void disk_access() {
	CLOCKS += 5000;
	DISKACCESSES++;
	// update BUF
	// update PT
	// update L2
	// update TLB
	// update L1
	if (TESTFLOW == 1) printf("Disk Accessed\n");
	return;
}


void L2_Access() {
	// simulate 4-way set associative by searching all 4 L2 Arrays
	unsigned int index = ca.L2Index;
	if (L2ArrA[index].frame == ca.fn) { // hit A
		// update TLB
		updateTLB();
		// update L1
		if (TESTFLOW == 1) printf("L2Ahit\n");
	}
	else if (L2ArrB[index].frame == ca.fn) { // hit B
		// update TLB
		updateTLB();
		// update L1
		if (TESTFLOW == 1) printf("L2Bhit\n");
	}
	else if (L2ArrC[index].frame == ca.fn) { // hit C
		// update TLB
		updateTLB();
		// update L1
		if (TESTFLOW == 1) printf("L2Chit\n");
	}
	else if (L2ArrD[index].frame == ca.fn) { // hit D
		// update TLB
		updateTLB();
		// update L1

		if (TESTFLOW == 1) printf("L2Dhit\n");
	}
	else { // miss entire L2 cache
		if (TESTFLOW == 1) printf("L2 miss\n");
	}
}


// update appropriate L1cache:
void updateL1() {
	CLOCKS += 4; // updating L1 costs clocks
	if (ca.typeOfAccess == 'I') {  // update L1I cache
		L1IArr[ca.L1Index].page = ca.pn;
		L1IArr[ca.L1Index].v = 1;
		if (TESTFLOW == 1) printf("Updating L1I... \n");
	}
	else { // update L1D cache
		L1DArr[ca.L1Index].page = ca.pn;
		L1DArr[ca.L1Index].v = 1;
		if (TESTFLOW == 1) printf("Updating L1D... \n");
	}
	return;
}


// update the L2cache:
void updateL2() {
	CLOCKS += 12;
	L2LRU(); // set global to correct LRU L2cache
	unsigned int index = ca.L2Index;
	if (L2_LRU == 'a') {
		L2ArrA[index].frame;
	}
	//else if (L2_LRU == 'b')
	//else if (L2_LRU == 'c')
	//else if (L2_LRU == 'd')
}

void updateTLB() {
	// accessing TLB costs no clocks
	TLBArr[TLBPTR].frame = ca.fn;
	TLBArr[TLBPTR].v = 1;
	TLBPTR++;
}

#endif
