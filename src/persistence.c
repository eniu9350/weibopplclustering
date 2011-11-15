#include "persistence.h"

#include "aws.h"
#include <time.h>


int insertPplState(ppl* p)
{
	char url[1000];
	int len_headers=6;
	httpRequestHeader* headers = (httpRequestHeader*)malloc(len_headers*sizeof(httpRequestHeader));
	strcat(headers[0].name, "ItemName");
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
	printf("insertpplstate url=\n%s\n", url);	
}

