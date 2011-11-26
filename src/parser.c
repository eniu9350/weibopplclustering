#include "wbpc.h"

#include "ppl.h"

#include "parser.h"

#include <sys/types.h>
#include <regex.h>

#include <string.h>
ppl* parsePersonalPage(htmlContent* h, UINT uid)
{	
	printf("in parseeeeeeeeeeeeeeeeeeeeeeeee\n");
	//printf("content=======%s\n", h->content);
	char pattern[300] = "<em class=\"MIB_txtal\">([0-9]+)</em>.*</span><span><em class=\"MIB_txtal\">([0-9]+)</em>.*</span><span><em class=\"MIB_txtal\">([0-9]+)</em>微博</span>";
	regex_t reg;
	//reg matches
	regmatch_t regm[10];
	int ret;
	char* snow;
	char tmp[100];
	int tmplen;
	char* s0;
	printf("-----------1---\n");
	//sprintf(pattern,"<li><a href=\\\"\\\\/%d\\\\/follow\\\"><strong>([0-9]*)<\\\\/strong>[.*]<strong>([0-9]*)<\\\\/strong><span>\\\\u5fae\\\\u535a<\\\\/span>", uid);
	//	sprintf(pattern,"<strong>([0-9]*)", ')');
	//char pattern[300] = "com/[A-Za-z0-9]*\" target=\"_blank\" suda-uatrack=\"key=apex_top&value=all\">([ \t\n\r]*)([^<\t\r\n]+)([ \t\n\r]*)</a>([ \t\n\r]*)</span>([ \t\n\r]*)</td>([ \t\n\r]*)<td class=\"aln_rt\"><span class=\"times_zw\">([0-9]+)</span>";
	//char pattern[100] = "key=apex_top&value=all";

	printf("-----------2---pattern=%s\n", pattern);
	if( (regcomp(&reg, pattern, REG_EXTENDED)) !=0 )
	{
		printf("could not compile regex");
		exit(1);
	}

	printf("-----------3---\n");
	ret = regexec(&reg, h->content, 5, regm, 0);
	snow = s0 = h->content;
	//printf("reg[0]so=%d,eo=%d", regm[0].rm_so,regm[0].rm_eo);	
	//store result
	ppl* p = createPpl();

	printf("-----------4---\n");
	// nfoing
	tmplen = regm[1].rm_eo-regm[1].rm_so;
//	printf("-----------tmplen=%d---\n",tmplen);
	memcpy(tmp, snow+regm[1].rm_so, tmplen);	
	tmp[tmplen]='\0';	
//	printf("-----------tmp=%s---\n",tmp);
	p->nfoing=atoi(tmp);

//	printf("-----------5---\n");
	//a. name
	tmplen = regm[3].rm_eo-regm[3].rm_so;
	memcpy(tmp, snow+regm[3].rm_so, tmplen);
	tmp[tmplen]='\0';	
	printf("-----------tmp=%s---\n",tmp);
	p->nsaying=atoi(tmp);
//	printf("-----------6---\n");

//	printf("break\n");
	return p;
}

ppllist* parseIndexPage(htmlContent* h)
{
	//	printf("content size= %d\n", strlen(h->content));
	ppllist* ppls;
	regex_t reg;
	//reg matches
	regmatch_t regm[20];
	char group[100];
	int i;
	int ret;
	char* snow;
	char tmp[100];
	int tmplen;
	char* s0;

	ppls = createPpllist();
	printf("init ppls size=%d\n", ppls->size);


	char pattern[500] = "uid=\"([0-9]+)\"[ \t\n\r]*usercard=\"true\" [ \t\n\r]*href=\"http://weibo\\.com/([A-Za-z0-9_]*)\" target=\"_blank\" suda-uatrack=\"key=apex_top&value=all\">([ \t\n\r]*)([^<\t\r\n]+)([ \t\n\r]*)</a>([ \t\n\r]*)</span>([ \t\n\r]*)</td>([ \t\n\r]*)<td class=\"aln_rt\"><span class=\"times_zw\">([0-9]+)</span>";
	//char pattern[300] = "com/[A-Za-z0-9]*\" target=\"_blank\" suda-uatrack=\"key=apex_top&value=all\">([ \t\n\r]*)([^<\t\r\n]+)([ \t\n\r]*)</a>([ \t\n\r]*)</span>([ \t\n\r]*)</td>([ \t\n\r]*)<td class=\"aln_rt\"><span class=\"times_zw\">([0-9]+)</span>";
	//char pattern[100] = "key=apex_top&value=all";
	//char pattern[500] = "uid=\"([0-9]+)\"[ \t\n\r]*usercard=\"true\" [ \t\n\r]*href=\"http://weibo\\.com/([A-Za-z0-9_]*)\" target=\"_blank\" suda-uatrack=\"key=apex_top&value=all\">([ \t\n\r]*)([^<\t\r\n]+)([ \t\n\r]*)</a>([ \t\n\r]*)</span>([ \t\n\r]*)</td>([ \t\n\r]*)<td class=\"aln_rt\"><span class=\"times_zw\">([0-9]+)</span>";

	if( (regcomp(&reg, pattern, REG_EXTENDED)) !=0 )
	{
		printf("could not compile regex");
		exit(1);
	}

//	printf("----1----\n");
	ret = regexec(&reg, h->content, 15, regm, 0);
//	printf("----1.5----\n");
	snow = s0 = h->content;
	while(!ret){
		//printf("reg[0]so=%d,eo=%d", regm[0].rm_so,regm[0].rm_eo);	
		//store result
		ppl* p = createPpl();

//	printf("----2----\n");
		// uid
		tmplen = regm[1].rm_eo-regm[1].rm_so;
		memcpy(tmp, snow+regm[1].rm_so, tmplen);	
		tmp[tmplen]='\0';	
		p->uid = atoi(tmp);
		printf("regm1=%s, tmplen=%d, uid=%d\n",tmp,tmplen,p->uid);

		// url part 
		tmplen = regm[2].rm_eo-regm[2].rm_so;
		memcpy(tmp, snow+regm[2].rm_so, tmplen);	
		tmp[tmplen]='\0';	
		strcpy(p->urlpart, tmp);

		//a. name
		tmplen = regm[4].rm_eo-regm[4].rm_so;
		memcpy(tmp, snow+regm[4].rm_so, tmplen);
		tmp[tmplen]='\0';	
		strcpy(p->name, tmp);
		printf("name=%s\n", p->name);

		//b. number
		tmplen = regm[9].rm_eo-regm[9].rm_so;
		memcpy(tmp, snow+regm[9].rm_so, tmplen);
		tmp[tmplen]='\0';	
		p->nfoer=atoi(tmp);
		printf("n=%d\n", p->nfoer);

		//z. add
		addPpl(ppls, p);


		snow += regm[0].rm_eo ;
		//printf("offset=%d\n", snow-s0);

		//search again
		ret = regexec(&reg, snow, 15, regm, 0);
		//break;
	}
//	printf("break\n");
//	printf("after break, pplssize=%d\n", ppls->size);
	return ppls;
}
