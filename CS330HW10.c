// Thomas Evon
// CS 330
// main file

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"CS330HW10Functions.h"
#include"CS330HW10Globals.h"
#define LSIZ 128
#define RSIZ 8

int main()
{

	init_arrays(); // initialize all arrays

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

    for(i = 0; i < tot; ++i) { // loop through each line of txt file

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
		unsigned int convertedHex = convert(hexStr); // convert hex->unsignedint
		ca.va = convertedHex; // store hex into struct
		unsigned int Offset = returnOffset(convertedHex);
		ca.offset = Offset; // save offset into struct
		unsigned int pageNumber = returnPageNumber(convertedHex);
		ca.pn = pageNumber; // save pageNumber into struct
		ca.L1Index = ca.va >> 4; // shift off byte_selctor bits
		ca.L1Index = ca.L1Index & 511; // 511 = 0x1FF mask
		ca.L2Index = ca.va >> 5; // shift off byte_selctor bits
		ca.L2Index = ca.L2Index & 1023; // 1023 = 0x3FF mask
		ca.TLBIndex = ca.pn & 255; // 255 = 0xFF mask
		ca.PTIndex = ca.pn & 262143; // 262143 = 0x3FFFF mask

		// process everything - simulate virtual memory
		if (ca.typeOfAccess == 'I') L1I_Access();
		else L1D_Access();

		L2LRU();
		printf("%s %c \n", "L2_LRU = ", L2_LRU);

    }

	return 0;
}
