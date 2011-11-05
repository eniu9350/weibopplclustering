#ifndef _WBPC_PPL_H_
#define _WBPC_PPL_H_

#include "wbpc.h"

typedef struct ppl
{
	char name[32];
	UINT nsaying;
	UINT nfoer;
	UINT nfoing;

	//speed of saying
	UINT spsay;
	//speed of being followed
	UINT spfo;

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

#endif
