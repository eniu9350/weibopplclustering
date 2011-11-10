#include "wbpc.h"
#include "crawler.h"
#include "ppl.h"

int main(int argc, char* argv[])
{
	ppllist* ppls;
	int i;
	ppl* p;
	ppls = crawlPpls();
	printf("end of main, ppls size=%d\n", ppls->size);
	for(i=0;i<3;i++)	{
		p = &ppls->list[i];
		printf("[MAIN]uid=%d,nsaying=%d,nfoer=%d,nfoing=%d\n", p->uid, p->nsaying, p->nfoer, p->nfoing);
	}


	/*
	   char urlpersonal[100];
	   htmlContent h;
	   htmlContent hpersonal;
	   ppllist* ppls;
	   ppl* p;
	   ppl* padd;
	   int i;

	   h.len=0;
	   h.content=(char*)malloc(1);
	   hpersonal.len=0;
	   hpersonal.content=(char*)malloc(1);

	 */

}
