#include "wbpc.h"
#include "crawler.h"
#include "ppl.h"

#include "aws.h"

int main(int argc, char* argv[])
{

	char tosign[1000];
	httpRequestHeader* headers;
	headers = (httpRequestHeader*)malloc(3*sizeof(httpRequestHeader));
	strcpy(headers[0].name, "k0");
	strcpy(headers[0].value, "k0");
	strcpy(headers[1].name, "k1");
	strcpy(headers[1].value, "k1");
	strcpy(headers[2].name, "k2");
	strcpy(headers[2].value, "k2");
	getStringToSign(tosign, HTTP_METHOD_GET, "ListDomain", headers, 3); 	
	printf("tosign=%s\n", tosign);


/*
	ppllist* ppls;
	int i;
	ppl* p;

	htmlContent h;
	
	h.len=0;
	h.content=(char*)malloc(1);
	strcpy(h.url, "http://data.weibo.com/top/ajax/hot?page=5&class=0001&depart=0001&_t=0&__rnd=1320929132670");
	crawl(&h);
	printf("new crawl,result=%s\n", h.content);

	ppls = crawlPpls();
	printf("end of main, ppls size=%d\n", ppls->size);
	for(i=0;i<ppls->size;i++)	{
		p = &ppls->list[i];
		printf("[MAIN]uid=%d,nsaying=%d,nfoer=%d,nfoing=%d\n", p->uid, p->nsaying, p->nfoer, p->nfoing);
	}
*/

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
