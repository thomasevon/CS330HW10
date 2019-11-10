// Thomas Evon
// CS 330
// CS330HW10Globals.h
// header file that contains all globals used for CS330HW10.c

#ifndef CS330HW10GLOBALS_H
#define CS330HW10GLOBALS_H

// constants:
int L1SIZE = 512;
int L2SIZE = 1024;
int PTSIZE = 170000; // actual size should be 2^20, 1048576
int TLBSIZE = 256;
int FTSIZE = 170000; // actual size should be 2^24, 16777216
int BUFSIZE = 16; 

// globals:
int CLOCKS;				// total process clocks
int	L1IACCESSES;	 	// total L1I total accesses
int	L1IHITS;			// total L1I hits
int L1DACCESSES;		// total L1D total accesses
int L1DHITS;			// total L1D hits
int	L2ACCESSES;			// total L2 accesses
int L2HITS;				// total L2 hits
int BUFACCESSES;		// total buffer accesses
int DISKACCESSES;		// total disk accesses
int TLBACCESSES;		// total TLB accesses
int TLBHITS;			// total TLB hits
int	PAGEFAULTS;			// total page faults

// structs:
struct ca {
	char typeOfAccess;
	unsigned int va, pn, fn, offset, pa, L1Index, L2Index;
	int bytes; 
}; // currentAccess struct


struct L1I {
	int v, d;
	unsigned int page;
};


struct L1D {
	int v, d;
	unsigned int page;
};


struct L2 {
	int v, d;
	unsigned int frame;
};

struct TLB {
	int v;
	unsigned int frame, page;
};

struct FT {
	unsigned int frame;
	int* freePtr; 	
};

struct BUF {
	int v, d;
	unsigned int frame; 
};

struct PT {
	int v, d;
	unsigned int frame; 
};

// instantiate structures:
struct ca ca;			
struct L1I L1I;
struct L1D L1D;
struct L2 L2; 
struct TLB TLB;
struct PT PT;
struct BUF BUF; 
struct FT FT;

#endif 