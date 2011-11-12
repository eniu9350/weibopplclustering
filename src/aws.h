#ifndef _WBPC_PPL_H_
#define _WBPC_PPL_H_

#include "wbpc.h"


typedef int httpRequestMethod;
#define HTTP_METHOD_GET 1
#define HTTP_METHOD_POST 2
#define STR_HTTP_METHOD_GET "GET" 
#define STR_HTTP_METHOD_POST "POST" 
#define LEN_HTTP_METHOD_GET 3
#define LEN_HTTP_METHOD_POST 4

typedef struct httpRequestHeader{
	char name[30];
	char value[128];
}httpRequestHeader;

#define fillMethodString(s, m) { 	\
	if(m==HTTP_METHOD_GET) {	\
		strcpy(s, STR_HTTP_METHOD_GET); \
		s += LEN_HTTP_METHOD_GET; \
	} else if(m==HTTP_METHOD_POST)	{\
		strcpy(s, STR_HTTP_METHOD_POST);\
		s += LEN_HTTP_METHOD_POST;	\
	}	\ 
}	

#define fillHeaderString(s, h) strcpy(s, (h)->name);s+=strlen((h)->name);strcpy(s,(h)->value);s+=strlen((h)->value);



//------common----------
int getStringToSign(char* result, httpRequestMethod method, httpRequestHeader* headers, int nheaders);

//------spec------------


int createDomain(char* dn);

#endif
