#include "aws.h"
#include "b64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>

void getGMTString(char* s)
{
	time_t ltime;
	struct tm* gtime;

	time(&ltime);
	gtime = gmtime(&ltime);
	sprintf(s, "%d-%02i-%02iT%02i%%3A%02i%%3A%02i.000Z", 1900+gtime->tm_year, 1+gtime->tm_mon, gtime->tm_mday, gtime->tm_hour, gtime->tm_min, gtime->tm_sec);
}

int getStringToSign(char* result, httpRequestMethod method, char* action, httpRequestHeader* headers, int nheaders)
{
	char* tosign;
	char gmt[30];
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
	getGMTString(gmt);
	fillTimestamp(tosign, gmt);
	fillVersion(tosign);
	return 0;
}

int signString(char* tosign, char* signature)
{
	char* hmacstr;
	int hmaclen;
	char* base64str;
	char* urlecstr;
	CURL* curl = curl_easy_init();
	unsigned char* key = (unsigned char*) AWS_SECRETACCESSKEYID;
	HMAC_CTX ctx;

	hmaclen = 1000;
	hmacstr = (unsigned char*) malloc(sizeof(char) * hmaclen);

	ENGINE_load_builtin_engines();
	ENGINE_register_all_complete();

	HMAC_CTX_init(&ctx);
	HMAC_Init_ex(&ctx, key, LEN_AWS_SECRETACCESSKEYID, EVP_sha1(), NULL);
	HMAC_Update(&ctx, tosign, strlen(tosign));
	HMAC_Final(&ctx, hmacstr, &hmaclen);
	HMAC_CTX_cleanup(&ctx);

	printf("hmac=%s\n", hmacstr);


	printf("----------------base64 encoded\n");;
	base64str = base64(hmacstr, strlen(hmacstr));
	//printf("%s\n", base64str);

	urlecstr = curl_easy_escape(curl, base64str, strlen(base64str));
	if(urlecstr)	{
		strcpy(signature, urlecstr);
		//printf("%s\n", urlecstr);
		curl_free(urlecstr);
	}else{
		printf("err\n");
	}
	curl_easy_cleanup(curl);
}

int getUrlString(char* result, httpRequestMethod method, char* action, httpRequestHeader* headers, int nheaders)
{
	char tosign[1000];
	char signature[1000];
	char gmt[100];
	int i;

	getStringToSign(tosign, method, action, headers, nheaders);
	signString(tosign, signature);
	printf("-----------tosign=\n%s\n",tosign);

	sprintf(result, "https://sdb.amazonaws.com/?Action=%s", action);
	strcpy(result+strlen(result), "&Version=2009-04-15");
	strcpy(result+strlen(result),"&AWSAccessKeyId=");
	strcpy(result+strlen(result),AWS_ACCESSKEYID); 
	strcpy(result+strlen(result),"&SignatureVersion=2");
	strcpy(result+strlen(result),"&SignatureMethod=HmacSHA1");
	strcpy(result+strlen(result), "&Timestamp=");
	getGMTString(gmt);	
	strcpy(result+strlen(result), gmt);
	strcpy(result+strlen(result), "&Signature=");
	strcpy(result+strlen(result), signature);

	for(i=0;i<nheaders;i++)	{
		strcpy(result+strlen(result), "&");
		strcpy(result+strlen(result), headers[i].name);
		strcpy(result+strlen(result), "=");
		strcpy(result+strlen(result), headers[i].value);
	}


}


int listDomain()
{
	char tosign[1000];
	char signature[1000];
	char url[2000];
	/*
	   httpRequestHeader* headers;

	   headers = (httpRequestHeader*)malloc(3*sizeof(httpRequestHeader));
	   strcpy(headers[0].name, "DomainName");
	   strcpy(headers[0].value, "k0");
	   strcpy(headers[1].name, "Att1");
	   strcpy(headers[1].value, "k1");
	   strcpy(headers[2].name, "Att2");
	   strcpy(headers[2].value, "k2");
	 */
	/*
	   getStringToSign(tosign, HTTP_METHOD_GET, "ListDomain", headers, 3); 	
	   printf("tosign=%s\n", tosign);
	   signString(tosign, signature);
	   printf("sign=%s\n", signature);
	 */

	getUrlString(url, HTTP_METHOD_GET, "ListDomains", 0, 0); 	
	printf("url===%s\n", url);

}
int createDomain(char* dn)
{

}

