#include <stdio.h>
#define PATH_MAX 30

int compare_files(FILE *in, FILE *out){
    char c1, c2;

    while(((c1 = fgetc(in)) != EOF) && ((c2 =fgetc(out)) != EOF)){
        printf("c1 = %c c2 = %c\n", c1, c2);
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

    fprintf(stderr, "d");
    FILE *fp = popen("stdbuf -oL ./graph_cli", "w");
    int status;
    char path[PATH_MAX];

    int test_status[5];
    
    
    
    if (fp == NULL)
        /* Handle error */;
        
    
    fgets(path, PATH_MAX, fp);
        printf("%s", path);

    fprintf(stderr, "d");

    manual_graph(3, 3, fp, 2);
    // 3 mnode and 3 edges graph 
    fprintf(fp, "0 1\n");
    fprintf(fp, "0 2\n");
    fprintf(fp, "2 1\n");
    fprintf(fp, "yes\n");
    fprintf(fp, "test\n");
    
    
    
    status = pclose(fp);

    FILE *out = fopen("./output/test", "r");
    FILE *in = fopen(argv[1], "r");

    printf("\n");

    if(compare_files(out, in)){
        test_status[0] = 1;
    }else{
        test_status[0] = 0;
    }
    
    //second test 
    
        fprintf(stderr, "d");
        fp = popen("stdbuf -oL ./graph_cli", "w");

        
        
        
        if (fp == NULL)
            /* Handle error */;
            
        
        fgets(path, PATH_MAX, fp);
            printf("%s", path);
    
        fprintf(stderr, "d");
    
        manual_graph(3, 3, fp, 1);
        // 3 mnode and 3 edges graph 
        fprintf(fp, "0 1\n");
        fprintf(fp, "0 2\n");
        fprintf(fp, "2 1\n");
        fprintf(fp, "yes\n");
        fprintf(fp, "test\n");
        
        
        
        status = pclose(fp);
    
        out = fopen("./output/test", "r");
        in = fopen(argv[2], "r");
    
        printf("\n");
    
        if(compare_files(out, in)){
            test_status[1] = 1;
        }else{
            test_status[1] = 0;
        }


    //third test, wrong input
    fprintf(stderr, "d");
        fp = popen("stdbuf -oL ./graph_cli", "w");

        
        
        
        if (fp == NULL)
            /* Handle error */;
            
        
        fgets(path, PATH_MAX, fp);
            printf("%s", path);
    
        fprintf(stderr, "d");
    
        manual_graph(3, 5, fp, 1);
        // 3 mnode and 3 edges graph 
        fprintf(fp, "0 1\n");
        fprintf(fp, "0 1\n"); //this edge exists
        fprintf(fp, "2 7\n"); // node index out of range
        fprintf(fp, "0 4\n");
        fprintf(fp, "2 4\n");
        fprintf(fp, "yes\n");
        fprintf(fp, "test\n");
        
        
        
        status = pclose(fp);
    
        out = fopen("./output/test", "r");
        in = fopen(argv[3], "r");
    
        printf("\n");
    
        if(compare_files(out, in)){
            test_status[2] = 1;
        }else{
            test_status[2] = 0;
        }

        //third test, wrong input
        fprintf(stderr, "d");
        fp = popen("stdbuf -oL ./graph_cli", "w");

        
        
        
        if (fp == NULL)
            /* Handle error */;
            
        
        fgets(path, PATH_MAX, fp);
            printf("%s", path);
    
        fprintf(stderr, "d");
    
        manual_graph(5, 5, fp, 2);
        fprintf(fp, "0 1\n");
        fprintf(fp, "0 2\n"); 
        fprintf(fp, "2 3\n"); 
        fprintf(fp, "0 4\n");
        fprintf(fp, "2 4\n");
        fprintf(fp, "yes\n");
        fprintf(fp, "test\n");
        
        
        
        status = pclose(fp);
    
        out = fopen("./output/test", "r");
        in = fopen(argv[4], "r");
    
        printf("\n");
    
        if(compare_files(out, in)){
            test_status[3] = 1;
        }else{
            test_status[3] = 0;
        }
        
        fprintf(stderr, "d");
        fp = popen("stdbuf -oL ./graph_cli", "w");

        
        
        
        if (fp == NULL)
            /* Handle error */;
            
        
        fgets(path, PATH_MAX, fp);
            printf("%s", path);
    
        fprintf(stderr, "d");
    
        
        fprintf(fp, "2\n");
        fprintf(fp, "generate me a graph with 3 nodes and 3 edges\n"); 
        fprintf(fp, "yes\n");
        fprintf(fp, "test\n");
        
        
        
        status = pclose(fp);
    
        out = fopen("./output/test", "r");
        in = fopen(argv[4], "r");
    
        printf("\n");
    
        if(compare_files(out, in)){
            test_status[4] = 1;
        }else{
            test_status[4] = 0;
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
