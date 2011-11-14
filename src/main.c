#include "wbpc.h"
#include "crawler.h"
#include "ppl.h"

#include "aws.h"

#include "time.h"
#include "b64.h"
#include <curl/curl.h>

int _getStringToSign(char* result, httpRequestMethod method, char* action, httpRequestHeader* headers, int nheaders)
{
	char* tosign;
	char gmt[30]="2011-11-14T02%3A19%3A28.000Z";
	int i,j;
	httpRequestHeader** sortedHeaders;
	httpRequestHeader* tmpHeader;
	httpRequestHeader* maxHeader;

	tosign = result;

	sortedHeaders = (httpRequestHeader**)malloc((nheaders+1)*sizeof(httpRequestHeader*));

	sortedHeaders[0] = (httpRequestHeader*)malloc(sizeof(httpRequestHeader));
	strcpy(sortedHeaders[0]->name,"Action");
	strcpy(sortedHeaders[0]->value,action);
	for(i=0;i<nheaders;i++)	{
		sortedHeaders[i+1] = headers+i;
	}
	for(i=0;i<(nheaders+1);i++)	{
		for(j=0;j<=(nheaders+1)-2-i;j++)	{
			if(strcmp(sortedHeaders[j],sortedHeaders[j+1])>0)	{
				tmpHeader = sortedHeaders[j];
				sortedHeaders[j] = sortedHeaders[j+1];
				sortedHeaders[j+1] = tmpHeader;
			}
		}
	}

	fillMethodString(tosign, method);
	fillAwsUrl(tosign);
	fillAwsPath(tosign);
	fillAwsAccessKeyId(tosign);
	//fillAction(tosign, action);

	for(i=0;i<nheaders+1;i++)	{
		fillHeaderString(tosign, sortedHeaders[i]);
	}

	fillSignatureMethod(tosign);
	fillSignatureVersion(tosign);
	fillTimestamp(tosign, gmt);
	fillVersion(tosign);
	return 0;

}

int main2(int argc, char* argv[])
{
	char* tosign[1000];
	char* signature[1000];

	_getStringToSign(tosign, HTTP_METHOD_GET, "ListDomains", 0, 0); 	
	signString(tosign, signature);
	printf("test tosign=%s\n", tosign);
	printf("test signature=%s\n", signature);

}
int main(int argc, char* argv[])
{

	httpRequestHeader* headers;
	char tosign[1000];
	char* hmacstr;
	int hmaclen;
	char* base64str;
	char* urlecstr;
	CURL* curl = curl_easy_init();

	char* signature[1000];


	time_t ltime;
	struct tm* gtime;

	//for hmac
	unsigned char* key = (unsigned char*) "AKIAJTTNRZHW4KIPQXNA";
	HMAC_CTX ctx;
	hmaclen = 1000;
	hmacstr = (unsigned char*) malloc(sizeof(char) * hmaclen);

	time(&ltime);
	gtime = gmtime(&ltime);
	printf("%d,%d,%d\n", 1900+gtime->tm_year, 1+gtime->tm_mon, gtime->tm_mday);
	printf("%d,%d,%d\n", gtime->tm_hour, gtime->tm_min, gtime->tm_sec);

	listDomain();

	/*
	   headers = (httpRequestHeader*)malloc(3*sizeof(httpRequestHeader));
	   strcpy(headers[0].name, "DomainName");
	   strcpy(headers[0].value, "k0");
	   strcpy(headers[1].name, "Att1");
	   strcpy(headers[1].value, "k1");
	   strcpy(headers[2].name, "Att2");
	   strcpy(headers[2].value, "k2");
	   getStringToSign(tosign, HTTP_METHOD_GET, "ListDomain", headers, 3); 	
	 */
	/*
	   printf("tosign=%s\n", tosign);
	   signString(tosign, signature);
	   printf("sign=%s\n", signature);
	 */

	/*
	   printf("----------------hmac signature\n");;

	   ENGINE_load_builtin_engines();
	   ENGINE_register_all_complete();

	   HMAC_CTX_init(&ctx);
	   HMAC_Init_ex(&ctx, key, 20, EVP_sha256(), NULL);
	   HMAC_Update(&ctx, tosign, strlen(tosign));
	   HMAC_Final(&ctx, hmacstr, &hmaclen);
	   HMAC_CTX_cleanup(&ctx);

	   printf("%s\n", hmacstr);


	   printf("----------------base64 encoded\n");;
	   base64str = base64(hmacstr, strlen(hmacstr));
	   printf("%s\n", base64str);


	   urlecstr = curl_easy_escape(curl, base64str, strlen(base64str));
	   if(urlecstr)	{
	   printf("%s\n", urlecstr);
	   curl_free(urlecstr);
	   }else{
	   printf("err\n");
	   }
	   curl_easy_cleanup(curl);
	 */
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
