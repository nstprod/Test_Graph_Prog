
#include <stdio.h>

#ifndef __PARSER_H__
#define __PARSER_H__

int compare_files(FILE *in, FILE *out);
int analyze_graph( int e, int n, FILE *out, int type, FILE *testfile);
#endif