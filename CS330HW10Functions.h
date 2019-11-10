// Thomas Evon
// CS 330
// CS330HW10Functions.h
// header file that contains all of the utility functions used for CS330HW10.c

#ifndef CS330HW10GFUNCTIONS_H
#define CS330HW10GFUNCTIONS_H

//------------------------------------------------------------------------
// Utility Functions:

int convertToInt(char* inChar) {
	int returnInt = atoi(inChar);
	return returnInt; 
}

char * stripString(char* inStr, int lower, int upper) {
	inStr[upper];
	strncpy(inStr, inStr+lower, upper);
	inStr[upper] = '\0'; 

	return inStr;
}


// returns a decimal value for virtual OFFSET
unsigned int returnOffset(unsigned int decimalAddress) {
	unsigned int mask =   4095; /* 0xFFF */
	unsigned int extract = mask & decimalAddress;
	return extract; 
}


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

#endif 
