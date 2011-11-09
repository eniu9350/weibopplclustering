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
	printf("init ppls size=%d\n", ppls->size);
	
	
	char pattern[200] = "\"key=apex_top&value=all\">([ \t\n\r]*)([^<\t\r\n]+)([ \t\n\r]*)</a>([ \t\n\r]*)</span>([ \t\n\r]*)</td>([ \t\n\r]*)<td class=\"aln_rt\"><span class=\"times_zw\">([0-9]+)</span>";
	//char pattern[100] = "key=apex_top&value=all";

	if( (regcomp(&reg, pattern, REG_EXTENDED)) !=0 )
	{
		printf("could not compile regex");
		exit(1);
	}

	ret = regexec(&reg, h->content, 10, regm, 0);
	snow = s0 = h->content;
	while(!ret){
		//printf("reg[0]so=%d,eo=%d", regm[0].rm_so,regm[0].rm_eo);	
		//store result
		ppl* p = createPpl();

		//a. name
		memcpy(tmp, snow+regm[2].rm_so, regm[2].rm_eo-regm[2].rm_so);
		tmp[regm[2].rm_eo-regm[2].rm_so]='\0';	
		strcpy(p->name, tmp);
		printf("name=%s\n", p->name);

		//b. number
		memcpy(tmp, snow+regm[7].rm_so, regm[7].rm_eo-regm[7].rm_so);
		tmp[regm[7].rm_eo-regm[7].rm_so]='\0';
		p->nfoer=atoi(tmp);
		printf("n=%d\n", p->nfoer);
		
		//z. add
		addPpl(ppls, p);


		snow += regm[0].rm_eo ;
		//printf("offset=%d\n", snow-s0);

		//search again
		ret = regexec(&reg, snow, 10, regm, 0);
		//break;
	}
	printf("break\n");
	printf("after break, pplssize=%d\n", ppls->size);
	return ppls;
}
