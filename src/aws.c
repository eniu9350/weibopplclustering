#include "aws.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStringToSign(char* result, httpRequestMethod method, httpRequestHeader* headers, int nheaders)
{
	int i;
	fillMethodString(result, method);
	for(i=0;i<nheaders;i++)	{
		fillHeaderString(result, headers+i);
	}
	return 0;
}

int createDomain(char* dn)
{
		
}

