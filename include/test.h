#include <stdio.h>
#ifndef __TEST_H__
#define __TEST_H__


int handle_test_case(FILE * fp, int opt, FILE  * testfile);
void print_test_status(int *status, int n);
void add_entry(FILE *testfile, const char* format, ...);

#endif