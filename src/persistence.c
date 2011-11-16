#include "persistence.h"

#include "aws.h"
#include <time.h>
#include "httputil.h"

static size_t cbPutAttributes(void* contents, size_t size, size_t nmemb, void* userp)
{

	size_t realsize = size * nmemb;
	htmlContent* h = (htmlContent*)userp;
	int* result;

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
	

	if(strstr(h->content, "Response>"))	{
		result = (int*)h->z;
		if(strstr(h->content, "<Errors>"))	{
				*((int*)h->z) = 1;
			}
			else{
				*((int*)h->z) = 0;
			}
	}
}

//0:success, 1:error reply, -1:not completed
int insertPplState(ppl* p)
{
	
	char url[1000];
	int len_headers=6;
	htmlContent* h;
	int result;

	printf("inserting ppl state...\n");

	httpRequestHeader* headers = (httpRequestHeader*)malloc(len_headers*sizeof(httpRequestHeader));
	strcpy(headers[0].name, "ItemName");
	sprintf(headers[0].value,"%d%c%ld",p->uid, AWS_API_KEY_SEPARATOR, p->ts);
	strcpy(headers[1].name, "Attribute.1.Name");
	strcpy(headers[1].value, "nfoer");
	strcpy(headers[2].name, "Attribute.1.Value");
	sprintf(headers[2].value, "%d",p->nfoer);
	strcpy(headers[3].name, "Attribute.2.Name");
	strcpy(headers[3].value, "nsaying");
	strcpy(headers[4].name, "Attribute.2.Value");
	sprintf(headers[4].value, "%d",p->nsaying);
	strcat(headers[5].name, "DomainName");
	strcpy(headers[5].value, "weibopplclustering");
	//strcpy(headers[4].value, p->nsaying);
	getUrlString(url, HTTP_METHOD_GET, AWS_API_SDB_NAME_PUTATTRIBUTE, headers, len_headers);
	//	httpGet(url, cbPutAttributes, 
	printf("insertpplstate url=\n%s\n", url);	

	result = -1;	//0:success, 1:error reply, -1:not completed
	h = createHtmlContent();
	h->z = (void*)&result;
	httpGet(url, cbPutAttributes, h);
	return *((int*)h->z);
}
