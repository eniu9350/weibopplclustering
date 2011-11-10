#include "wbpc.h"

#include "crawler.h"

#include "ppl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

static size_t WriteMemoryCallBack(void* contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	htmlContent* h = (htmlContent*)userp;

	ppllist* ppls;
	ppl* p;
	ppl* padd;
	int i;
	//char urlpersonal[100];
	htmlContent* hpersonal;


	//printf("in wrmem, url=%s\n",h->url);
	h->content = (char*)realloc(h->content, h->len+realsize+1);
	//	printf("in wrmem, after realloc\n");
	if(h->content == NULL)
	{
		printf("not enough memory (realloc returned NULL)\n");
		exit(EXIT_FAILURE);
	}

	memcpy(&(h->content[h->len]), contents, realsize);
	h->len += realsize;
	h->content[h->len] = 0;


	if(strstr(h->content, "</html>"))	{
		printf("end of html!!!!!!!!!!!!!, url=%s\n", h->url);
		if(strstr(h->url, "famous"))	{//index page
			printf("famous, famous--\n");
			ppls = parseIndexPage(h);
			h->z = (void*)ppls;
			//printf("after parse\n");
//			for(i=0;i<ppls->size;i++)	{
			for(i=0;i<ppls->size;i++)	{
				p = &ppls->list[i];
				hpersonal = (htmlContent*)malloc(sizeof(htmlContent));
				//printf("urlpart=%s\n",p->urlpart);
				sprintf(hpersonal->url, "http://weibo.com/%s", p->urlpart);
				//printf("urlpart copied=%s\n",hpersonal->url);
				hpersonal->len=0;
				hpersonal->content=(char*)malloc(1);
				hpersonal->z=p;
				crawl(hpersonal);
			}
		}
		else {
			//printf("personal, personal--\n");
			p=(ppl*)h->z;
			padd = parsePersonalPage(h, p->uid);
			//printf("pname=%s\n",p->name);
			p->nfoing = padd->nfoing;
			p->nsaying = padd->nsaying;
			//printf("personal, personal--end\n");
			free(padd);
			printf("[in iteration]%s,foer=%d, foing%d, uid=%d,nsaying=%d,urlpart=%s\n",p->name, p->nfoer,p->nfoing, p->uid,p->nsaying,p->urlpart);

		}
	}


	//	printf("in wrmem, url=%s end_____________\n",h->url);
	return realsize;
}

int crawl(htmlContent* h)
{

	CURL* curl;

	//temp
	char* strDisplay;

	//struct MemoryStruct chunk;
	//chunk.memory = malloc(1);
	//chunk.size = 0;


	//	printf("crawl 1, hurl=%s\n",h->url);
	//printf("crawl 2\n");

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, h->url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallBack);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)h);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	//printf("crawl 3\n");
	if(curl)
	{
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	printf("%lu bytes retrieved\n", (long)h->len);

	//just for display
	//strDisplay = (char*)malloc(111201);
	//memcpy(strDisplay, h->content, 111200);
	//strDisplay[111200] = '\0';
	//printf("\nincrawl, content=%s\n", strDisplay);

	//if(h->content)
	//{
	//   free(h->content);
	//}

	curl_global_cleanup();
	return 0;
}

void crawlPpls(){
	htmlContent h;
	h.len=0;
	h.content=(char*)malloc(1);

	strcpy(h.url, "http://data.weibo.com/top/hot/famous");
	crawl(&h);
}
