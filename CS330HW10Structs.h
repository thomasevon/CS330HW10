// Thomas Evon
// CS 330
// CS330HW10Structs.h
// header file that contains all structs used for CS330HW10.c

struct ca {
	char typeOfAccess;
	unsigned int va, pn, fn, offset, pa, L1Index, L2Index;
	int bytes; // this is not currently used, but needs to be
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