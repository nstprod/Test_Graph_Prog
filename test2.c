#include <stdio.h>
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
// type 1 - directed graph 2 - undirected graph
void manual_graph(int e, int n, FILE *fp, int type){
    fprintf(fp, "1\n");
    fprintf(fp, "1\n");
    fprintf(fp, "%d\n", type);
    fprintf(fp, "%d\n", n);
    fprintf(fp, "%d\n", e);
}

void test(FILE * fp, int opt){

    switch (opt) {
        case 1:
            manual_graph(3, 3, fp, 2);
            // 3 mnode and 3 edges graph 
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 2\n");
            fprintf(fp, "2 1\n");
            fprintf(fp, "yes\n");
            fprintf(fp, "test\n");
            break;
        case 2:
            manual_graph(3, 3, fp, 1);
            // 3 mnode and 3 edges graph 
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 2\n");
            fprintf(fp, "2 1\n");
            fprintf(fp, "yes\n");
            fprintf(fp, "test\n");
            break;
        case 3:
            manual_graph(3, 5, fp, 1);
            // 3 mnode and 3 edges graph 
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 1\n"); //this edge exists
            fprintf(fp, "2 7\n"); // node index out of range
            fprintf(fp, "0 4\n");
            fprintf(fp, "2 4\n");
            fprintf(fp, "yes\n");
            fprintf(fp, "test\n");
            break;

        case 4:
            manual_graph(5, 5, fp, 2);
            fprintf(fp, "0 1\n");
            fprintf(fp, "0 2\n"); 
            fprintf(fp, "2 3\n"); 
            fprintf(fp, "0 4\n");
            fprintf(fp, "2 4\n");
            fprintf(fp, "yes\n");
            fprintf(fp, "test\n");
            break;

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

    for (int i = 1; i <= 4 ; i++){

        FILE *fp = popen("stdbuf -oL ./graph_cli", "w");
    
        if (fp == NULL)
            /* Handle error */;
           
        fgets(path, PATH_MAX, fp);
            printf("%s", path);

        fprintf(stderr, "d");

        test(fp, i);
        
        status = pclose(fp);

        FILE *out = fopen("./output/test", "r");
        FILE *in = argc > i ? fopen(argv[i], "r") : NULL;
        if (in == NULL){
            printf("Provide comparison file");
            return 1;
        }
        printf("\n");
        if (in != NULL && out != NULL){
            if(compare_files(out, in)){
                test_status[i-1] = 1;
            }else{
                test_status[i-1] = 0;
            }
        }
    }
    print_test_status(test_status);
    if (status == -1) {
        /* Error reported by pclose() */
        
    } else {
        /* Use macros described under wait() to inspect `status' in order
           to determine success/failure of command executed by popen() */
        
    }
    return 0;
}
