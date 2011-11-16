#include "httputil.h"

int httpGet(char* url, size_t (*callback)(void*,size_t,size_t,void*), htmlContent* data)
{
	CURL* curl;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)data);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	//printf("crawl 3\n");
	if(curl)
	{
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	//printf("%lu bytes retrieved\n", (long)h->len);
}

//create html content for crawl
htmlContent* createHtmlContent()
{
	htmlContent* h = (htmlContent*)malloc(sizeof(htmlContent));
	h->len=0;
	h->content = (char*)malloc(1);
	return h;
}


