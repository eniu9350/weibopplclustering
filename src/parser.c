#include "wbpc.h"

#include "ppl.h"

#include "parser.h"

#include <sys/types.h>
#include <regex.h>

#include <string.h>

ppllist* parse(htmlContent *h)
{
//	printf("content size= %d\n", strlen(h->content));
	ppllist* ppls;
	regex_t reg;
	//reg matches
	regmatch_t regm[10];
	char group[100];
	int i;
	int ret;
	char* snow;
	char tmp[100];
	char* s0;

	ppls = createPpllist();
	
	
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
		printf("reg[0]so=%d,eo=%d", regm[0].rm_so,regm[0].rm_eo);	
		
		
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
	printf("break\n");
}
