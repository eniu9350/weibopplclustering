#include "wbpc.h"
#include "crawler.h"
#include "parser.h"
#include "ppl.h"

int main(int argc, char* argv[])
{
	char url[100] = "http://data.weibo.com/top/hot/famous";
	htmlContent h;
	ppllist* ppls;
	int i;

	h.len=0;
	h.content=(char*)malloc(1);

	crawl(url, &h);

	ppls = parse(&h);
	printf("after parse\n");
	for(i=0;i<ppls->size;i++)	{
		printf("[in iteration]%s,%d\n",ppls->list[i].name, ppls->list[i].nfoer);
	}
}
