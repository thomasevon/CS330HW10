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
	printf("%s%d\n", "3. Total disk accesses: ", DISKACCESSES);
	printf("%s%d\n", "4. Total buffer accesses: ", BUFACCESSES);

	int L1Ihits = L1IHITS;
	int L1Iaccesses = L1IACCESSES;
	double L1IHitRate = (double)L1Ihits / (double)L1Iaccesses;
	printf("%s%f\n", "5. L1I hit rate: ", L1IHitRate);

	int L1Dhits = L1DHITS;
	int L1Daccesses = L1DACCESSES;
	double L1DHitRate = (double)L1Dhits / (double)L1Daccesses;
	printf("%s%f\n", "6. L1D hit rate: ", L1DHitRate);

	int TLBhits = TLBHITS;
	int TLBaccesses = TLBACCESSES;
	double TLBHitRate = (double)TLBhits / (double)TLBaccesses;
	printf("%s%f\n", "7. TLB hit rate: ", TLBHitRate);

	int L2hits = L2HITS;
	int L2accesses = L2ACCESSES;
	double L2HitRate = (double)L2hits / (double)L2accesses;
	printf("%s%f\n", "8. L2 hit rate: ", L2HitRate);

	printf("%s%d\n", "9. Last TLB pointter: ", TLBPTR);

	printf("\n");
	printf("%s\n", "---------------------------------------------------------");
}

// generate ca.pa, ca.L2Index
void generatePA() {
	// pre: ca must have a fn loaded in
	// post: ca.pa, ca.L2Index are created
	// generate pa
	unsigned int loader = ca.fn << 12; // shift fn left to prep for OR
	ca.pa = loader | ca.offset; // pa is generated

	// generate L2Index for L2_Access
	ca.L2Index = ca.pa >> 5; // shift off byte_selctor bits
	ca.L2Index = ca.L2Index & 1023; // 1023 = 0x3FF mask

	// create bufsector
	ca.bufsector = ca.pa >> 16;
	ca.bufsector = ca.bufsector & 65535; // mask by 0xFFFF to keep rightmost 16 bits
}


// displays array
void displayArray(int count) {
	for (int r = 0; r < count; r++){
		// printf("%s %u \n", "page: ", BUFArr[r].page);
		printf("%s %d \n", "frame: ", FTArr[r].frame);
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

	unsigned int runner = 262144;
	for (int f = 0; f < FTSIZE; f++) {
		FTArr[f].frame = runner;
		runner++; // shift to next available frame
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
		TLB_Access();
		if (TESTFLOW == 1) printf("L1I miss\n");
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
		TLB_Access();
		if (TESTFLOW == 1) printf("L1D miss\n");
	}
	return;
}


void TLB_Access() {
	// TLB doesn't cost any clocks
	TLBACCESSES++;
	int hitIndex;
	int hit = 0; // flag to indicate if there is a hit
	for (int index = 0; index <TLBSIZE; index++) { // linear search of TLB
		if (TLBArr[index].page = ca.pn && TLBArr[index].v == 1) // hit
			hit = 1;
			hitIndex = index;
	}

	if (hit == 1) {
		TLBHITS++;
		// generate pa and fn and store into ca:
		ca.fn = TLBArr[hitIndex].frame; // store frame into ca from TLB
		generatePA(); // store pa and L2Index into ca struct
		L2_Access(); // access L2
		if (TESTFLOW == 1) printf("TLB hit\n");
	}
	else if (hit == 0) { // miss
		PT_Lookup(); // access Page Table, will give pack fn
		updateTLB();
		generatePA(); // store pa and L2Index into ca struct
		L2_Access();
		if (TESTFLOW == 1) printf("TLB updated\n");
	}
	return;
}

void PT_Lookup() {
	CLOCKS += 50;
	unsigned int index = ca.PTIndex;
	if (PTArr[index].v == 1) { // hit
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


void disk_Access() {
	CLOCKS += 5000;
		DISKACCESSES++;
		// update page table:
		PTArr[ca.PTIndex].frame = ca.fn;
		PTArr[ca.PTIndex].v == 1;
		generatePA();
		BUFSECTOR = ca.bufsector;
		if (TESTFLOW == 1) printf("Disk Accessed\n");

	return;
}


void L2_Access() {
	L2ACCESSES++;
	// simulate 4-way set associative by searching all 4 L2 Arrays
	unsigned int index = ca.L2Index;
	if (L2ArrA[index].frame == ca.fn && L2ArrA[index].v == 1) { // hit A
		L2HITS++;
		updateL1();
		if (TESTFLOW == 1) printf("L2Ahit\n");
	}
	else if (L2ArrB[index].frame == ca.fn && L2ArrB[index].v == 1) { // hit B
		L2HITS++;
		updateL1();
		if (TESTFLOW == 1) printf("L2Bhit\n");
	}
	else if (L2ArrC[index].frame == ca.fn && L2ArrC[index].v == 1) { // hit C
		L2HITS++;
		updateL1();
		if (TESTFLOW == 1) printf("L2Chit\n");
	}
	else if (L2ArrD[index].frame == ca.fn && L2ArrD[index].v == 1) { // hit D
		L2HITS++;
		updateL1();
		if (TESTFLOW == 1) printf("L2Dhit\n");
	}
	else { // miss entire L2 cache
		PT_Lookup();
		updateTLB();
		updateL2();
		updateL1();
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
		L2ArrA[index].frame = ca.fn;
		L2ArrA[index].v = 1;
	}
	else if (L2_LRU == 'b') {
		L2ArrB[index].frame = ca.fn;
		L2ArrB[index].v = 1;
	}
	else if (L2_LRU == 'c') {
		L2ArrC[index].frame = ca.fn;
		L2ArrC[index].v = 1;
	}
	else if (L2_LRU == 'd') {
		L2ArrD[index].frame = ca.fn;
		L2ArrD[index].v = 1;
	}
}


void updateTLB() {
	// accessing TLB costs no clocks
	TLBArr[TLBPTR].frame = ca.fn;
	TLBArr[TLBPTR].page = ca.pn;
	TLBArr[TLBPTR].v = 1;
	TLBPTR++;
}


void updatePT() {
	CLOCKS += 50;
	PTArr[ca.PTIndex].frame = FTArr[FREEPTR].frame >> 12; // pull in frame from freeTable
	PTArr[ca.PTIndex].v == 1;
	ca.fn = FTArr[FREEPTR].frame; // update ca frame with new frame
	generatePA();
	BUFSECTOR = ca.bufsector; // update the buffer
	FREEPTR++;
}

#endif
