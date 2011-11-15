#ifndef _WBPC_PPL_H_
#define _WBPC_PPL_H_

#include "wbpc.h"

#include <time.h>

typedef struct ppl
{
	char name[32];
	UINT nsaying;
	UINT nfoer;
	UINT nfoing;

	//timestamp
	time_t ts;

	//speed of saying
	UINT spsay;
	//speed of being followed
	UINT spfo;

	//---only for convinience, not for mining---
	UINT uid;
	char urlpart[32];
	
} ppl;

typedef struct ppllist
{
	int size;
	ppl* list;
	int capacity;
}ppllist;

#define PPLLIST_INIT_CAPACITY 50
#define PPLLIST_CAPACITY_INC 50
#define PPLLIST_CAPACITY_MAX 8000

ppl* createPpl();
ppllist* createPpllist();
int expandPpllist(ppllist* p);
int addPpl(ppllist* l, ppl* p);
int pplcpy(ppl* p1, ppl* p2);
#endif
