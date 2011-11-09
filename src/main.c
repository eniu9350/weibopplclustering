#include "wbpc.h"
#include "crawler.h"
#include "parser.h"
#include "ppl.h"

int main(int argc, char* argv[])
{
	char url[100] = "http://data.weibo.com/top/hot/famous";
	htmlContent h;
	ppl** ppls;
	int nppls;

	h.len=0;
	h.content=(char*)malloc(1);

	crawl(url, &h);

	ppls = parse(&h);

}
