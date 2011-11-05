#ifndef _WBPC_PARSER_H_
#define _WBPC_PARSER_H_

#include "wbpc.h"

#include "ppl.h"

/*
h: html page content
ppls: parsed people
n: count of people
*/
int parse(htmlContent *h, ppl* ppls, int *n);

#endif