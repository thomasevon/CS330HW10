// Thomas Evon
// CS 330
// main file //

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"CS330HW10Functions.h"
#include"CS330HW10Globals.h"

int main() {

	init_arrays(); // initialize all arrays

	// read in file, store in 2d array
	char line[RSIZ][LSIZ];
	char fname[20] = "addstream.txt";
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
		strncpy(hexStr, processStr + 1, 8); // isolate the hex value
		hexStr[8] = '\0';
		unsigned int convertedHex = convert(hexStr); // convert hex->unsignedint
		ca.va = convertedHex; // store hex into struct
		unsigned int Offset = returnOffset(convertedHex);
		ca.offset = Offset; // save offset into struct
		unsigned int pageNumber = returnPageNumber(convertedHex);
		ca.pn = pageNumber; // save pageNumber into struct
		ca.L1Index = ca.va >> 4; // shift off byte_selctor bits
		ca.L1Index = ca.L1Index & 511; // 511 = 0x1FF mask
		// pre-process complete

		// run through process:
		if (ca.typeOfAccess == 'I') {
			// if (TESTFLOW == 1) printf("L1I_Access\n");
			L1I_Access();
		}
		else {
			// if (TESTFLOW == 1) printf("L1D_Access\n");
			L1D_Access();
		}
    }
	generateReport(); // print out final report and exit
	return 0;
}
