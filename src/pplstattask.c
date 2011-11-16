
#include "pplstattask.h"

#include <time.h>
#include "crawler.h"
#include "ppl.h"

extern ppllist* ppls;

int savePplStat(int interval)
{
	//get ppl list from sdb
	ppl* p;
	int i;
	time_t ltime;
	
	//crawl each ppl	
	for(i=0;i<ppls->size;i++)	{
		crawlPpl(ppls->list+i);
	}
	
	//get time and save
	time(&ltime);
	for(i=0;i<ppls->size;i++)	{
		p = &ppls->list[i];
		p->ts = ltime;
		insertPplState(ppls->list+i);	
	}
}

