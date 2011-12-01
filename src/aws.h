#ifndef _WBPC_AWS_H_
#define _WBPC_AWS_H_

#include "wbpc.h"

#include "awskey.h"

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


#define LINE_BREAK "\n"
#define LEN_LINE_BREAK 1
#define fillLineBreak(s) strcpy(s,LINE_BREAK);s+=LEN_LINE_BREAK;

#define AND "&"
#define LEN_AND 1
#define fillAnd(s) strcpy(s,AND);s+=LEN_AND;

#define EQUALS "="
#define LEN_EQUALS 1
#define fillEquals(s) strcpy(s,EQUALS);s+=LEN_EQUALS;

#define fillMethodString(s, m) { 	\
	if(m==HTTP_METHOD_GET) {	\
		strcpy(s, STR_HTTP_METHOD_GET); \
		s += LEN_HTTP_METHOD_GET; \
	} else if(m==HTTP_METHOD_POST)	{\
		strcpy(s, STR_HTTP_METHOD_POST);\
		s += LEN_HTTP_METHOD_POST;	\
	}	\
	fillLineBreak(s);	\
}	

#define fillHeaderString(s, h) fillAnd(s);strcpy(s, (h)->name);s+=strlen((h)->name);fillEquals(s);strcpy(s,(h)->value);s+=strlen((h)->value);

#define AWS_URL "sdb.amazonaws.com"
#define LEN_AWS_URL 17
#define fillAwsUrl(s) strcpy(s,AWS_URL);s+=LEN_AWS_URL;fillLineBreak(s);

#define AWS_PATH "/"
#define LEN_AWS_PATH 1
#define fillAwsPath(s) strcpy(s,AWS_PATH);s+=LEN_AWS_PATH;fillLineBreak(s);

#define AWS_NAME_ACCESSKEYID "AWSAccessKeyId"
#define LEN_AWS_NAME_ACCESSKEYID 14
//#define AWS_ACCESSKEYID "AAAAAAAAAAAAAA"
#define LEN_AWS_ACCESSKEYID 20
#define fillAwsAccessKeyId(s) strcpy(s,AWS_NAME_ACCESSKEYID);s+=LEN_AWS_NAME_ACCESSKEYID;fillEquals(s);strcpy(s,AWS_ACCESSKEYID);s+=LEN_AWS_ACCESSKEYID;

//#define AWS_SECRETACCESSKEYID "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
#define LEN_AWS_SECRETACCESSKEYID 40

#define AWS_NAME_ACTION "Action"
#define LEN_AWS_NAME_ACTION 6
#define fillAction(s, a) fillAnd(s);strcpy(s,AWS_NAME_ACTION);s+=LEN_AWS_NAME_ACTION;fillEquals(s);strcpy(s,(a));s+=strlen(a);

#define AWS_NAME_SIGNATUREMETHOD "SignatureMethod"
#define LEN_AWS_NAME_SIGNATUREMETHOD 15
#define AWS_SIGNATUREMETHOD "HmacSHA1"
#define LEN_AWS_SIGNATUREMETHOD 8
#define fillSignatureMethod(s) fillAnd(s);strcpy(s,AWS_NAME_SIGNATUREMETHOD);s+=LEN_AWS_NAME_SIGNATUREMETHOD;fillEquals(s);strcpy(s,AWS_SIGNATUREMETHOD);s+=LEN_AWS_SIGNATUREMETHOD;

#define AWS_NAME_SIGNATUREVERSION "SignatureVersion"
#define LEN_AWS_NAME_SIGNATUREVERSION 16
#define AWS_SIGNATUREVERSION "2"
#define LEN_AWS_SIGNATUREVERSION 1
#define fillSignatureVersion(s) fillAnd(s);strcpy(s,AWS_NAME_SIGNATUREVERSION);s+=LEN_AWS_NAME_SIGNATUREVERSION;fillEquals(s);strcpy(s,AWS_SIGNATUREVERSION);s+=LEN_AWS_SIGNATUREVERSION;

#define AWS_NAME_TIMESTAMP "Timestamp"
#define LEN_AWS_NAME_TIMESTAMP 9
#define fillTimestamp(s,t) fillAnd(s);strcpy(s,AWS_NAME_TIMESTAMP);s+=LEN_AWS_NAME_TIMESTAMP;fillEquals(s);strcpy(s,t);s+=strlen(t);	//temp!!

#define AWS_NAME_VERSION "Version"
#define LEN_AWS_NAME_VERSION 7
#define AWS_VERSION "2009-04-15"
#define LEN_AWS_VERSION 10
#define fillVersion(s) fillAnd(s);strcpy(s,AWS_NAME_VERSION);s+=LEN_AWS_NAME_VERSION;fillEquals(s);strcpy(s,AWS_VERSION);s+=LEN_AWS_VERSION;

#define AWS_API_SDB_NAME_PUTATTRIBUTE "PutAttributes"


#define AWS_API_KEY_SEPARATOR '-'

void getGMTString(char* s);
//------common----------
int getStringToSign(char* result, httpRequestMethod method, char* action, httpRequestHeader* headers, int nheaders);
int signString(char* tosign, char* signature);
//------spec------------


int getUrlString(char* result, httpRequestMethod method, char* action, httpRequestHeader* headers, int nheaders);
int listDomain();
int createDomain(char* dn);

#endif
