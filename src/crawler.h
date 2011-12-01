#ifndef _WBPC_CRAWLER_H_
#define _WBPC_CRAWLER_H_

#include "wbpc.h"
#include "ppl.h"

int crawl(htmlContent* h);

//ppllist* crawlPpls();
ppllist* crawlPpls(char* urlparts[]);

static size_t cbCrawlPpl(void* contents, size_t size, size_t nmemb, void* userp);
int crawlPpl(ppl* p, int n);
#endif
