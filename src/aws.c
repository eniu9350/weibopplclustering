#include "aws.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStringToSign(char* result, httpRequestMethod method, char* action, httpRequestHeader* headers, int nheaders)
{
	char *tosign;
	int i;
	
	tosign = result;

	fillMethodString(tosign, method);
	fillAwsUrl(tosign);
	fillAwsPath(tosign);
	fillAwsAccessKeyId(tosign);
	fillAction(tosign, action);

	for(i=0;i<nheaders;i++)	{
		fillHeaderString(tosign, headers+i);
	}

	fillSignatureMethod(tosign);
	fillSignatureVersion(tosign);

	fillTimestamp(tosign);
	return 0;
}

int createDomain(char* dn)
{

}

