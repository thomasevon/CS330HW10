// Big Program
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"CS330HW10Functions.h"
#include"CS330HW10Globals.h"
#define LSIZ 128 
#define RSIZ 8

// constants:
int L1SIZE = 512;
int L2SIZE = 1024;
int PTSIZE = 170000; // actual size should be 2^20, 1048576
int TLBSIZE = 256;
int FTSIZE = 170000; // actual size should be 2^24, 16777216
int BUFSIZE = 16; 

int main()
{	
	// declar arrays:
	struct L1I L1IArr[L1SIZE]; 
	struct L1D L1DArr[L1SIZE];
	struct L2 L2Arr[L2SIZE];
	struct TLB TLBArr[TLBSIZE];
	struct PT PTArr[PTSIZE];
	struct BUF BUFArr[BUFSIZE];
	struct FT FTArr[FTSIZE];

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
		L2Arr[c].v = 0;
		L2Arr[c].d = 0;
		L2Arr[c].frame = 0;
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

	// read in file
	char line[RSIZ][LSIZ];
	char fname[15] = "addstream.txt";
	char* processStr;
    FILE *fptr = NULL; 
	int i = 0;
	int tot = 0;
	

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) {
      	line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
	tot = i;  

    for(i = 0; i < tot; ++i) { // loop through each line of txt file stored in vector

		// pre-process - initialize the ca struct with values from addstream.txt
		processStr = line[i]; 
		scrubFileLine(processStr); // clean out spaces and commas in txt file 
		ca.typeOfAccess = processStr[0]; // store type into struct
		char bytesAccessedBuffer[1] = {'0'};
		bytesAccessedBuffer[0] = processStr[9];
		char convertBytesA[1]; 
		convertBytesA[0] = processStr[9];
		int bytesAccessed = convertToInt(convertBytesA);
		ca.bytes= bytesAccessed; // store bytes accessed into struct 
		char hexStr[8];
		strncpy(hexStr, processStr+1, 8); // isolate the hex value
		hexStr[8] = '\0';
		unsigned int convertedHex = convert(hexStr); // convert hex to unsigned int decimal value
		ca.va = convertedHex; // store hex into struct
		unsigned int Offset = returnOffset(convertedHex); 
		ca.offset = Offset; // save offset into struct
		unsigned int pageNumber = returnPageNumber(convertedHex); 
		ca.pn = pageNumber; // save pageNumber into struct

		// process everything - simulate memory mapping

    } 

	return 0;
}
