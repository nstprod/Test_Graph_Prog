#include <stdio.h>
#ifndef __COM_H__
#define __COM_H__

void add_edge(FILE * fp, FILE *exp_out, int n1, int n2, int d, int skip);
FILE * manual_mode(int i, int e, int n, FILE *fp, int type, int dir);
void llm_mode(FILE *fp, char * req);
char * save_test(FILE * fp, int i);
void add_entry(FILE *testfile, const char* format, ...);

#endif