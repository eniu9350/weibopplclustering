#ifndef _WBPC_TYPES_H_
#define _WBPC_TYPES_H_

#define UINT unsigned int
#define BOOL unsigned char

typedef struct htmlContent{
	char* url[100];
	UINT len;
	char* content;
	void* z;
}htmlContent;

#endif

