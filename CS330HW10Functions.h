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
void generatePA();
void updatePT();

// accessors
void disk_Access();
void PT_Lookup();
void buf_Access();
void L2_Access();
void TLB_Access();
void L1I_Access();
void L1D_Access();

//------------------------------------------------------------------------
// Utility Functions:

// generates the final report to spit out
void generateReport() {
	printf("%s\n", "---------------------------------------------------------");
	printf("%s\n\n", "This is the report for the addstream.txt process: ");
	printf("%s%d\n", "1. Total Clocks Required: ", CLOCKS);
	printf("%s%d\n", "2. Total Page Faults: ", PAGEFAULTS);
	printf("%s%d\n", "3. Total buffer hits: ", BUFHITS);

	int L1Ihits = L1IHITS;
	int L1Iaccesses = L1IACCESSES;
	double L1IHitRate = (double)L1Ihits / (double)L1Iaccesses;
	printf("%s%f\n", "4. L1I hit rate: ", L1IHitRate);

	int L1Dhits = L1DHITS;
	int L1Daccesses = L1DACCESSES;
	double L1DHitRate = (double)L1Dhits / (double)L1Daccesses;
	printf("%s%f\n", "5. L1D hit rate: ", L1DHitRate);

	int TLBhits = TLBHITS;
	int TLBaccesses = TLBACCESSES;
	double TLBHitRate = (double)TLBhits / (double)TLBaccesses;
	printf("%s%f\n", "6. TLB hit rate: ", L1DHitRate);

	int L2hits = L2HITS;
	int L2accesses = L2ACCESSES;
	double L2HitRate = (double)L2hits / (double)L2accesses;
	printf("%s%f\n", "7. L2 hit rate: ", L2HitRate);

	printf("%s%d\n", "8. Last TLB pointer: ", TLBPTR);
	printf("%s0x%x\n", "9. Last Frame Allocated: ", FREEPTR - 1);

	printf("\n");
	printf("%s\n", "---------------------------------------------------------");
}

// generate ca.pa, ca.L2Index
void generatePA() {
	// pre: ca must have a fn loaded in
	// post: ca.pa, ca.L2Index are created

	unsigned int loader = ca.fn << 12; // shift fn left to prep for OR
	ca.pa = loader | ca.offset; // pa is generated

	// generate L2Index for L2_Access
	ca.L2Index = ca.pa >> 5; // shift off byte_selctor bits
	ca.L2Index = ca.L2Index & 1023; // 1023 = 0x3FF mask

	// create bufsector
	ca.bufsector = ca.pa >> 14;
	//ca.bufsector = ca.bufsector & 65535; // mask by 0xFFFF to keep rightmost 16 bits
}


// displays array for testing
void displayArray(int count) {
	for (int r = 0; r < count; r++) {
		printf("%s %u \n", "TLB.v ", TLBArr[r].page);
		//printf("%s %d\n", ", valid: ", TLBArr[r].v);
	}
}


// discovers the least-recently used L2 cache
void L2LRU() {
	int sort[4];
	sort[0] = L2ArrA[0].used;
	sort[1] = L2ArrB[0].used;
	sort[2] = L2ArrC[0].used;
	sort[3] = L2ArrD[0].used;

	int min;
	int i = 0;
	int j = i + 1;
	for (i; i < 3; i++) { // sort for which L2 has the most recent uses
		if (sort[i] < sort[j])
			min = sort[i];
		else min = sort[j];
		j++;
	}
	for (int j = 0; j < 3; j++) {
		if (sort[j] < min)
			min = sort[j];
	}
	// set correct global L2_LRU global flag:
	if (min == L2ArrA[0].used) L2_LRU = 'a';
	else if (min == L2ArrB[0].used) L2_LRU = 'b';
	else if (min == L2ArrC[0].used) L2_LRU = 'c';
	else if (min == L2ArrD[0].used) L2_LRU = 'd';
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
		L1IHITS += 1;
		L1IArr[index].d = 1; // set dirty
		if (TESTFLOW == 1) printf("L1Ihit\n");
	}
	else { // miss
		if (TESTFLOW == 1) printf("L1I miss\n");
		TLB_Access();
	}
	return;
}


void L1D_Access() {
	CLOCKS += 4;
	L1DACCESSES++;
	unsigned int index = ca.L1Index; // ca.va[12-4]
	if (L1DArr[index].page == ca.pn && L1DArr[index].v == 1) {// hit
		L1DHITS += 1;
		L1DArr[index].d = 1; // set dirty
		if (TESTFLOW == 1) printf("L1Dhit\n");
	}
	else { // miss
		if (TESTFLOW == 1) printf("L1D miss\n");
		TLB_Access();
	}
	return;
}


void TLB_Access() {
	// TLB doesn't cost any clocks
	TLBACCESSES++;
	int hitIndex = 0;
	int hit = 0; // flag to indicate if there is a hit
	for (int index = 0; index < TLBSIZE; index++) { // linear search of TLB
		if (TLBArr[index].page == ca.pn && TLBArr[index].v == 1) { // flag as hit
			hit = 1;
			hitIndex = index;
			break;
		}
	}

	if (hit == 1) { // TLB hits
		TLBHITS++;
		if (TESTFLOW == 1) printf("TLB hit\n");
		// generate pa and fn and store into ca:
		ca.fn = TLBArr[hitIndex].frame; // store frame into ca from TLB
		generatePA(); // store pa and L2Index into ca struct
		L2_Access();
	}
	else if (hit == 0) { // miss
		if (TESTFLOW == 1) printf("TLB Mised\n");
		PT_Lookup(); // access Page Table, will give pack fn
		generatePA();
		updateTLB();
		if (TESTFLOW == 1) printf("TLB updated\n");
		L2_Access();
	}
	return;
}


void L2_Access() {
	L2ACCESSES++;
	// simulate 4-way set associative by searching all 4 L2 Arrays
	unsigned int index = ca.L2Index;

	if (L2ArrA[index].frame == ca.fn && L2ArrA[index].v == 1) { // hit A
		L2HITS++;
		if (TESTFLOW == 1) printf("L2Ahit\n");
		updateL1();
	}
	else if (L2ArrB[index].frame == ca.fn && L2ArrB[index].v == 1) { // hit B
		L2HITS++;
		if (TESTFLOW == 1) printf("L2Bhit\n");
		updateL1();
	}
	else if (L2ArrC[index].frame == ca.fn && L2ArrC[index].v == 1) { // hit C
		L2HITS++;
		if (TESTFLOW == 1) printf("L2Chit\n");
		updateL1();
	}
	else if (L2ArrD[index].frame == ca.fn && L2ArrD[index].v == 1) { // hit D
		L2HITS++;
		if (TESTFLOW == 1) printf("L2Dhit\n");
		updateL1();
	}
	else { // miss entire L2 cache
		CLOCKS += 50; // "access" main mem and increment clock
		if (TESTFLOW == 1) printf("L2 miss\n");
		updateL2();
		updateL1();
	}
}


// update appropriate L1cache:
void updateL1() {
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


void disk_Access() {
	if (TESTFLOW == 1) printf("Disk Accessed\n");
	if (ca.bufsector == BUFSECTOR) { // buffer hit
		BUFHITS++;
		CLOCKS += 200;
		updatePT();
	}
	else { // miss the buffer
	DISKACCESSES++;
	CLOCKS += 5000;
	updatePT();
	BUFSECTOR = ca.bufsector; // buffer now holds the last frame written back
	}
	return;
}


void PT_Lookup() {
	CLOCKS += 50;
	unsigned int index = ca.pn;
	if (PTArr[index].frame == ca.fn && PTArr[index].v == 1) { // hit
		ca.fn = PTArr[index].frame;
		if (TESTFLOW == 1) printf("PT hit\n");
	}
	else { // miss
		PAGEFAULTS++;
		if (TESTFLOW == 1) printf("Page Fault\n");
		disk_Access();
	}
	return;
}


// update the L2cache:
void updateL2() {
	if (TESTFLOW == 1) printf("updatingL2...\n");
	CLOCKS += 12;
	L2LRU(); // function will set global L2_LRU to the correct value
	unsigned int index = ca.L2Index;
	// check for which L2 to update:
	if (L2_LRU == 'a') {
		L2ArrA[index].frame = ca.fn;
		L2ArrA[index].v = 1;
		L2ArrA[0].used++;
	}
	else if (L2_LRU == 'b') {
		L2ArrB[index].frame = ca.fn;
		L2ArrB[index].v = 1;
		L2ArrB[0].used++;
	}
	else if (L2_LRU == 'c') {
		L2ArrC[index].frame = ca.fn;
		L2ArrC[index].v = 1;
		L2ArrC[0].used++;
	}
	else if (L2_LRU == 'd') {
		L2ArrD[index].frame = ca.fn;
		L2ArrD[index].v = 1;
		L2ArrD[0].used++;
	}
}


void updateTLB() {
	// accessing TLB costs no clocks
	if (TLBPTR == TLBSIZE) { // if at max entry, start over
		TLBPTR = 0;
	} // implement FIFO

	for (int i = 0; i < TLBSIZE; i++) { // if already in table, don't update
		if (TLBArr[i].page == ca.pn) { // check if TLB is already up to date
			return;
		}
	}
	// update the TLB:
	TLBArr[TLBPTR].frame = ca.fn;
	TLBArr[TLBPTR].page = ca.pn;
	TLBArr[TLBPTR].v = 1;
	TLBPTR++;
}


void updatePT() {
	CLOCKS += 50;
	unsigned int newFrame = FREEPTR; // new frame is the next in free list
	PTArr[ca.pn].frame = newFrame; // pull in frame from freeTable
	PTArr[ca.pn].v == 1;
	ca.fn = newFrame;
	FREEPTR++;
}

#endif
