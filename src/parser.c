#include "wbpc.h"

#include "ppl.h"

#include "parser.h"

#include <sys/types.h>
#include <regex.h>

#include <string.h>



int parse(htmlContent *h, ppl* ppls, int *n)
{
	printf("content size= %d\n", strlen(h->content));
	regex_t reg;
	//reg matches
	regmatch_t regm[10];
	char group[100];
	int i;
	int ret;
	char* snow;
	char tmp[100];
	char* s0;


	char pattern[100] = "\"key=apex_top&value=all\">([ \t\n\r]*)([^<\t\r\n]+)([ \t\n\r]*)</a>";
	//char pattern[100] = "key=apex_top&value=all";

	if( (regcomp(&reg, pattern, REG_EXTENDED)) !=0 )
	{
		printf("could not compile regex");
		exit(1);
	}


	ret = regexec(&reg, h->content, 10, regm, 0);
	snow = s0 = h->content;
	while(!ret){
		//debug
		memcpy(tmp, snow+regm[2].rm_so, regm[2].rm_eo-regm[2].rm_so);
		tmp[regm[2].rm_eo-regm[2].rm_so]='\0';	
		printf("#1#2=%d%d\n", tmp[0],tmp[1]);
		printf("after#x=%d%d\n", tmp[10],tmp[11]);
		printf("matched=(%s)\n", tmp);

		snow += regm[0].rm_eo ;

		printf("offset=%d\n", snow-s0);
		ret = regexec(&reg, snow, 10, regm, 0);
		//break;
	}

	for(i=0; i<3; i++)
	{
		memcpy(group, h->content+regm[i].rm_so, regm[i].rm_so-regm[i].rm_eo);
		group[regm[i].rm_so-regm[i].rm_eo] = '\0';
		printf("group %d = %s", i, group);
	}
}
