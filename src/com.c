#include <stdio.h>
#include <stdlib.h>
void add_edge(FILE * fp, FILE *exp_out, int n1, int n2, int d, int skip){
    fprintf(fp, "%d %d\n", n1, n2);
    if (skip) return; // used for cases where edges are wrong 
    if (d == 1)
        fprintf(exp_out, "    %d -> %d;\n", n1, n2);
    else if (d == 2)
        fprintf(exp_out, "    %d -- %d;\n", n1, n2);
}


// function to go through imput to manual graph generation
// type: 1 - manual  graph 2 - random graph
// dir: 1 - directed graph 2 - undirected graph

FILE * manual_mode(int i, int e, int n, FILE *fp, int type, int dir){
    char filename[50];
    fprintf(fp, "1\n");
    fprintf(fp, "%d\n", type);
    fprintf(fp, "%d\n", dir);
    fprintf(fp, "%d\n", n);
    fprintf(fp, "%d\n", e);
    if (type == 1){
        sprintf(filename, "./input/in%d.txt", i);
        FILE * expected_out = fopen (filename, "w");
        if (dir == 1)
            fprintf(expected_out, "digraph G {\n");
        else if (dir == 2)
            fprintf(expected_out, "graph G {\n");
        return expected_out;
    }

    return NULL;

}



void llm_mode(FILE *fp, char * req){
    fprintf(fp, "2\n");
    fprintf(fp, "%s", req);
}


char * save_test(FILE * fp, int i){
    static char filename[30];
    fprintf(fp, "yes\n");
    
    fprintf(fp, "test%d\n", i);
    snprintf(filename, sizeof(filename), "./output/test%d", i);
    return filename;
}

/*writes an entry to a test file and prints it on stdin*/
#include <stdarg.h>  // va_list
void add_entry(FILE *testfile, const char* format, ...){
    char text[100];
    va_list args;
    va_start(args, format);
    if (vsprintf(text, format, args) > 0) {
        if (testfile != NULL){
            fputs(text, testfile);
        }
        printf("%s", text);
    }
    va_end(args);
}



