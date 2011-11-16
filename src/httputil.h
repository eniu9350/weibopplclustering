#ifndef _WBPC_HTTPUTIL_H_
#define _WBPC_HTTPUTIL_H_

#include "wbpc.h"

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

typedef struct htmlContent{
	char* url[100];
	UINT len;
	char* content;
	void* z;
}htmlContent;


int httpGet(char* url, size_t (*callback)(void*,size_t,size_t,void*), htmlContent* data);

htmlContent* createHtmlContent();
#endif
