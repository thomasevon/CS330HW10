// Thomas Evon
// CS 330
// CS330HW10Globals.h
// header file that contains all globals used for CS330HW10.c //

#ifndef CS330HW10GLOBALS_H
#define CS330HW10GLOBALS_H

// constants:
#define L1SIZE 512
#define L2SIZE 1024
#define PTSIZE 1048576 // 2^20, 1048576
#define TLBSIZE 256
#define FTSIZE 12582912 // 3 * 2^22, 12582912 // this is probably unneccessary
#define BUFSIZE 16
#define LSIZ 20 // for txt input array
#define RSIZ 200000 // for txt input array

// globals:
int CLOCKS;						// total process clocks
int	L1IACCESSES;	 	 		// total L1I total accesses
int	L1IHITS;					// total L1I hits
int L1DACCESSES;				// total L1D total accesses
int L1DHITS;					// total L1D hits
int	L2ACCESSES;					// total L2 accesses
int L2HITS;						// total L2 hits
int BUFACCESSES;				// total buffer accesses
int DISKACCESSES;				// total disk accesses
int TLBACCESSES;				// total TLB accesses
int TLBHITS;					// total TLB hits
int	PAGEFAULTS;					// total page faults
char L2_LRU;					// least-recently used tracker for L2 cache
int TESTFLOW = 0;  				// gauge to turn on printf statements
int TLBPTR = 0;					// pointer to the next free entry in TLB array
unsigned int FREEPTR = 262144;  // first free entry contains this frame number
unsigned int BUFSECTOR = 0; 	// buffer sector


// structs:
struct ca {
	char typeOfAccess;
	unsigned int va, pn, fn, offset, pa, L1Index, L2Index, PTIndex, bufsector;
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
	int v, d, used;
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

// declar arrays:
struct L1I L1IArr[L1SIZE];
struct L1D L1DArr[L1SIZE];
struct L2 L2ArrA[L2SIZE];
struct L2 L2ArrB[L2SIZE];
struct L2 L2ArrC[L2SIZE];
struct L2 L2ArrD[L2SIZE];
struct TLB TLBArr[TLBSIZE];
struct PT PTArr[PTSIZE];
struct BUF BUFArr[BUFSIZE];
struct FT FTArr[FTSIZE];

#endif
