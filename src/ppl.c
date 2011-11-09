#include "ppl.h"

#include "stdio.h"
ppl* createPpl()
{
	ppl* p = (ppl*)malloc(sizeof(ppl));
	//some init
}

ppllist* createPpllist()
{
	ppllist* p = (ppllist*)malloc(sizeof(ppllist));
	p->list = (ppl*)malloc(PPLLIST_INIT_CAPACITY*sizeof(ppl));
	p->size = 0;
	p->capacity = PPLLIST_INIT_CAPACITY;
	return p;
}

int expandPpllist(ppllist* p)
{
	if(p->capacity >= PPLLIST_CAPACITY_MAX)	{
		printf("ppllist expansion failure: already at the largest capacity");
		return -1;
	}
	p->capacity = p->capacity+PPLLIST_CAPACITY_INC>PPLLIST_CAPACITY_MAX?PPLLIST_CAPACITY_MAX:p->capacity+PPLLIST_CAPACITY_INC;
	p->list = (ppl*)realloc(p->list, p->capacity*sizeof(ppl));
}

int addPpl(ppllist* l, ppl* p)
{
	if(l->size==l->capacity)	{
		if(expandPpllist(l))	{
			return -1;
		}
	}

	pplcpy(&l->list[l->size], p);
	l->size++;
}

int pplcpy(ppl* p1, ppl* p2)
{
	strcpy(p1->name, p2->name);
	p1->nsaying = p2->nsaying;
	p1->nfoer = p2->nfoer;
	p1->nfoing = p2->nfoing;

	p1->spsay = p2->spsay;
	p1->spfo = p2->spfo;
}
