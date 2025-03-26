#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com.h"

int compare_files(FILE *in, FILE *out){
    char c1, c2;
    int status;
    char target_line[50]; char buffer[50];
    char *cursor;
    
    while (fgets(target_line, sizeof(target_line), out) != NULL){
        status = 0;
        if (cursor == NULL) 
            in = fopen("./output/test", "r");
        while (fgets(buffer, sizeof(buffer), in) != NULL) {
            if (strstr(buffer, target_line) != NULL) {
                status = 1;
            }
        }
        if (status < 1) break;
    }
    /*
    while(((c1 = fgetc(in)) != EOF) && ((c2 =fgetc(out)) != EOF)){
        //printf("c1 = %c, c2 = %c\n", c1, c2);
        if(c1 != c2){
            result = 0;
        }
    }
    */
    
    return status;

}


int analyze_graph( int e, int n, FILE *out, int type, FILE *testfile){
    char ch;
    int a_e = 0; int a_n = 0; int a_t = 0; // actual edges, nodes, type
    int conditions[3] = {0};
    int n1, n2, r;
    int *nodes_values = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) nodes_values[i] = 0;
    int i = 0;
    char line[50];

    if (fgets(line, sizeof(line), out)) {
        add_entry(testfile, "    %s",line);
        if (type == 1) {
            if (strstr(line, "digraph")) conditions[0] = 1;
            else if (strstr(line, "graph")) a_t = 2;
        }
        else if (type == 2) {
            if (strstr(line, "graph")) conditions[0] = 1;
            else if (strstr(line, "digraph")) a_t = 1;
        }
    }

    if (conditions[0] == 1) a_t = type;
    

    
    while (fgets(line, sizeof(line), out)){
        add_entry(testfile, "    %s",line);
        if (sscanf(line, " %d%*s%d", &n1, &n2) == 2){
            
            if (n1 >= 0 && n1 < n)
                nodes_values[n1]++;
            if (n2 >= 0 && n2 < n)
                nodes_values[n2]++;
            a_e++;
        }
    }
    int *missing_nodes = malloc(sizeof(int)*n);
    add_entry(testfile, "> ANALYSIS:\n");
    add_entry(testfile, "    Nodes encountered: ");
    int m = 0;
    for (int i = 0; i < n; i++){
        if (nodes_values[i] > 0) {
            add_entry(testfile, "%d ", i);
            a_n++;
        }
        else missing_nodes[m++] = i ;
    }
    add_entry(testfile, "\n");
    if (m>0)
        for (int i = 0; i < m; i++)
                add_entry(testfile, "(!) MISSING node %d\n", missing_nodes[i]);
            
    if (a_n == n) conditions[1] = 1;
    if (a_e == e) conditions[2] = 1;

    
    add_entry(testfile, "    condition 1 (graph type)  is %s: %s (expected %s)\n",
         conditions[0] == 1 ? "  met" : "unmet", a_t == 1 ? "Directed" : "Undirected", type == 1 ? "Directed" : "Undirected");
    add_entry(testfile, "    condition 2 (node number) is %s: %d (expected %d)\n", conditions[1] == 1 ? "  met" : "unmet", a_n, n);
    add_entry(testfile, "    condition 3 (edge number) is %s: %d (expected %d)\n\n", conditions[2] == 1 ? "  met" : "unmet", a_e, e);

    if (conditions[0] == 1 &&
        conditions[1] == 1 &&
        conditions[2] == 1)
        return 1;
    else return 0;

}
