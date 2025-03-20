#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 30

int compare_files(FILE *in, FILE *out){
    char c1, c2;

    while(((c1 = fgetc(in)) != EOF) && ((c2 =fgetc(out)) != EOF)){
        if(c1 != c2){
            return 0;
        }
    }
    return 1;

}

// function to go through imput to manual graph generation
// type1: 1 - manual  graph 2 - random graph
// type2: 1 - directed graph 2 - undirected graph


void manual_mode(int e, int n, FILE *fp, int type1, int type2){
    fprintf(fp, "1\n");
    fprintf(fp, "%d\n", type1);
    fprintf(fp, "%d\n", type2);
    fprintf(fp, "%d\n", n);
    fprintf(fp, "%d\n", e);
}



void llm_mode(FILE *fp){
    fprintf(fp, "2\n");
}

void save_test(FILE * fp){
    fprintf(fp, "yes\n");
    fprintf(fp, "test\n");
}

int analyze_rgraph(int opt, int e, int n, FILE *out, int type){
    char ch;
    int a_e = 0; int a_n = 0; int a_t = 0; // actual edges, nodes, type
    int conditions[3] = {0};
    int n1, n2, r;
    int *nodes_values = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) nodes_values[i] = 0;
    int i = 0;
    char line[50];

    if (fgets(line, sizeof(line), out)) {
        printf("%s\n", line);
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
        if (sscanf(line, " %d%*s%d", &n1, &n2) == 2){
            //printf("%s \n n1 = %d n2 = %d \n", line, n1, n2);
            if (n1 >= 0 && n1 < n)
                nodes_values[n1]++;
            if (n2 >= 0 && n2 < n)
                nodes_values[n2]++;
            a_e++;
        }
    }

    printf("Test %d details: \n", opt);

    printf("Nodes encountered:\n");
    for (int i = 0; i < n; i++){
        if (nodes_values[i] > 0) {
            printf("%d\n", i);
            a_n++;
        }
        else printf("missing node %d\n", i);
    }

    if (a_n == n) conditions[1] = 1;
    if (a_e == e) conditions[2] = 1;

    
    printf("condition 1 (graph type)  = %d: type %d  (expected %d)\n", conditions[0], a_t, type);
    printf("condition 2 (node number) = %d: %d nodes (expected %d)\n", conditions[1], a_n, n);
    printf("condition 3 (edge number) = %d: %d edges (expected %d)\n\n", conditions[2], a_e, e);

    if (conditions[0] == 1 &&
        conditions[1] == 1 &&
        conditions[2] == 1)
        return 1;
    else return 0;

}

int test(FILE * fp, int opt, int argc, char **argv){
    char line[50];
    int g_type = 1;
    int e, n, d;
    char req[100];
    switch (opt) {
        case 1:
            manual_mode(3, 3, fp, g_type, 2);
            // 3 mnode and 3 edges graph 
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 2\n");
            fprintf(fp, "2 1\n");
            break;
        case 2:
            manual_mode(3, 3, fp, g_type, 1);
            // 3 mnode and 3 edges graph 
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 2\n");
            fprintf(fp, "2 1\n");
            break;
        case 3:
            manual_mode(3, 5, fp, g_type, 1);
            // 3 mnode and 3 edges graph 
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 1\n"); //this edge exists
            fprintf(fp, "2 7\n"); // node index out of range
            fprintf(fp, "0 4\n");
            fprintf(fp, "2 4\n");
            break;

        case 4:
            manual_mode(5, 5, fp, g_type, 2);
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 2\n"); 
            fprintf(fp, "2 3\n"); 
            fprintf(fp, "0 4\n");
            fprintf(fp, "2 4\n");
            break;
        case 5:
            g_type = 2;
            e = 10; n = 8; d = 1;
            break;
            
        case 6: 
            g_type = 3;
            e = 13; n = 11; d = 1;
            strcpy(req, "Create a directed graph with 11 vertices and 13 edges\n");
            break;

    }

    if (g_type == 2){
        manual_mode(e, n, fp, g_type, d);
    }
    else if (g_type == 3){
        llm_mode(fp);
        fprintf(fp, "%s", req);
        while (strstr(line, "Raw response:")){
            fgets(line, sizeof(line), fp);
        }
    }


    save_test(fp);
    FILE *out = fopen("./output/test", "r");
    pclose(fp);

    if (g_type == 1){
        FILE *in = argc > opt ? fopen(argv[opt], "r") : NULL;
        if (in == NULL){
            printf("Provide comparison file\n");
            return 0;
        }
        
        if (in != NULL && out != NULL){
            return compare_files(out, in);
        }
    }
    
    else if (g_type == 2 || g_type == 3){
        int r = analyze_rgraph(opt, e, n, out, d);
            return r;

    }
    

    
}


void print_test_status(int *status){

    for(int i =0; i<5; i++){
        if(status[i]==1){
            printf("Test[%d] passed\n",i+1);
        }else{
            printf("Test[%d] failed\n",i+1);
        }
    }

}

int main(int argc, char **argv){

    int status;
    char path[PATH_MAX];

    int test_status[5];

    for (int i = 1; i <= 6 ; i++){

        FILE *fp = popen("stdbuf -oL ./graph_cli", "w");
    
        if (fp == NULL)
            /* Handle error */;
           
        fgets(path, PATH_MAX, fp);
            printf("%s", path);

        int r = test(fp, i, argc, argv);
    
        test_status[i-1] = r;
    
    }
    print_test_status(test_status);
    
    return 0;
}
