#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com.h" 
#include "parser.h"

int handle_test_case(FILE * fp, int opt, FILE  * testfile){
    int result = 0; // success or failure of the test

    // buffer 
    char line[100];
    char req[100];

    // graph characteristics 
    int e, n, d; // edges, nodes, direction

    // distinction between 3 graphs: 1 - manually written
    //                               2 - randomly generated
    //                               3 - made with llm
    int g_type = 1;

    FILE *exp_out; // expected output, used for checking correctness of edges
    
    // 10 cases where 1-5 are manual added edges, 6-8 random graphs, 9-10 graphs made with llm
    switch (opt) {
        case 1:
            e = 3; n = 3; d = 2;
            exp_out = manual_mode(opt, e, n, fp, g_type, d);
            add_edge(fp, exp_out, 0, 1, d, 0);
            add_edge(fp, exp_out, 0, 2, d, 0);
            add_edge(fp, exp_out, 1, 2, d, 0);
            break;
        case 2:
            e = 4; n = 4; d = 1;
            exp_out = manual_mode(opt, e, n, fp, g_type, d);
            add_edge(fp, exp_out, 0, 1, d, 0);
            add_edge(fp, exp_out, 0, 2, d, 0);
            add_edge(fp, exp_out, 2, 1, d, 0);
            add_edge(fp, exp_out, 3, 1, d, 0);
            break;
        case 3:
            e = 4; n = 5;d = 1;
            exp_out = manual_mode(opt, e, n, fp, g_type, d);
            // 3 mnode and 3 edges graph 
            add_edge(fp, exp_out, 0, 1, d, 0);
            add_edge(fp, exp_out, 0, 2, d, 0);
            add_edge(fp, exp_out, 0, 2, d, 1);//this edge exists
            add_edge(fp, exp_out, 2, 7, d, 1); // node index out of range
            add_edge(fp, exp_out, 2, 4, d, 0);
            add_edge(fp, exp_out, 2, 3, d, 0);
            break;

        case 4:
            e = 5; n = 5;d = 2;
            exp_out = manual_mode(opt, e, n, fp, g_type, d);
            add_edge(fp, exp_out, 0, 4, d, 0);
            add_edge(fp, exp_out, 0, 2, d, 0);
            add_edge(fp, exp_out, 0, 1, d, 0);
            add_edge(fp, exp_out, 2, 4, d, 0);
            add_edge(fp, exp_out, 2, 3, d, 0);
            break;
        case 5:
            e = 25; n = 20;d = 2;
            exp_out = manual_mode(opt, e, n, fp, g_type, d);
            add_edge(fp, exp_out, 0, 1, d, 0);
            add_edge(fp, exp_out, 0, 2, d, 0);
            add_edge(fp, exp_out, 0, 3, d, 0);
            add_edge(fp, exp_out, 0, 4, d, 0);
            add_edge(fp, exp_out, 0, 5, d, 0);
            add_edge(fp, exp_out, 0, 6, d, 0);
            add_edge(fp, exp_out, 0, 7, d, 0);
            add_edge(fp, exp_out, 0, 8, d, 0);
            add_edge(fp, exp_out, 0, 9, d, 0);
            add_edge(fp, exp_out, 0, 10, d, 0);
            add_edge(fp, exp_out, 0, 11, d, 0);
            add_edge(fp, exp_out, 0, 12, d, 0);
            add_edge(fp, exp_out, 0, 13, d, 0);
            add_edge(fp, exp_out, 0, 14, d, 0);
            add_edge(fp, exp_out, 0, 15, d, 0);
            add_edge(fp, exp_out, 0, 16, d, 0);
            add_edge(fp, exp_out, 0, 17, d, 0);
            add_edge(fp, exp_out, 0, 18, d, 0);
            add_edge(fp, exp_out, 0, 19, d, 0);

            add_edge(fp, exp_out, 1, 2, d, 0);
            add_edge(fp, exp_out, 1, 3, d, 0);
            add_edge(fp, exp_out, 1, 4, d, 0);

            add_edge(fp, exp_out, 2, 3, d, 0);
            add_edge(fp, exp_out, 2, 4, d, 0);
            add_edge(fp, exp_out, 2, 5, d, 0);
   
            break;
        // random graphs
        case 6: 
            g_type = 2;
            e = 15; n = 5; d = 1;
            break;

        case 7:
            g_type = 2;
            e = 40; n = 20; d = 2;
            break;
        
        case 8:
            g_type = 2;
            e = 30; n = 9; d = 1;
            break;
        // graphs made with llm
        case 9: 
            g_type = 3;
            e = 13; n = 11; d = 2;
            strcpy(req, "Create an udirected graph with 11 vertices and 13 edges\n");
            break;
        case 10: 
            g_type = 3;
            e = 10; n = 5; d = 1;
            strcpy(req, "Create a directed graph with 5 vertices and 10 edges\n");
            break;

    }

    // print on stdin and write into a file info about graph characteristics depending on the type of graph (1-3)
    add_entry(testfile, "> DETAILS\n");

    add_entry(testfile, "    Enabled '%s'\n", g_type != 3 ? "manual parameters input" : "chat mode");

    if (g_type == 3){
        add_entry(testfile, "    Requested: %s", req);    // spaces are for readability
    }

    if (g_type != 3){
        add_entry(testfile, "    Enabled '%s'\n", g_type == 1 ? "manual edge input" : "Random graph");
        
    }

    add_entry(testfile, "    Enabled '%s' graph type\n", d == 1 ? "Directed" : "Undirected");
    
    add_entry(testfile, "    Asked for %d nodes\n", n);
    
    add_entry(testfile, "    Asked for %d edges\n", e);

    // proccess the random graph
    if (g_type == 2){
        exp_out = manual_mode(opt, e, n, fp, g_type, d);
    }

    // send request to llm and wait for response
    else if (g_type == 3){
        llm_mode(fp, req);
        printf("Waiting for AI response...\n");
        while (strstr(line, "Raw response:")){
            fgets(line, sizeof(line), fp);
        }
    }

    // save test through a program and open that test
    save_test(fp);
    FILE *out = fopen("./output/test", "r");

    pclose(fp); // close tested program 

    
    add_entry(testfile, "> PROGRAM OUTPUT\n");

    if (g_type == 1){
        //FILE *in = fopen(files[opt-1], "r"); // zmiana tu
        fprintf(exp_out, "}\n");
        //fputs("}", exp_out);
        if (exp_out == NULL){
            add_entry(testfile, "Eror: No comparison file\n");
        }
        
        if (exp_out != NULL && out != NULL){
            fclose(exp_out);
            char filename[50];
            sprintf(filename, "./input/in%d.txt", opt);
            FILE *exp_out = fopen(filename, "r");
            result = compare_files(out, exp_out);
            fclose(exp_out);
            fclose(out);
            out = fopen("./output/test", "r");
            while (fgets(line, sizeof(line), out))
                add_entry(testfile, "    %s",line);
        }
    }
    
    else if (g_type == 2 || g_type == 3){
        result = analyze_graph( e, n, out, d, testfile);

    }
    fclose(out);
    return result;
}

void print_test_status(int *status, int n){
    printf("RESULTS:\n");
    for(int i =0; i<n; i++){
        if(status[i]==1){
            printf("\033[0;32m"); //green color
            printf("Test[%d] passed\n",i+1);
            printf("\033[0m");
        }else{
            printf("\033[0;31m"); //red color
            printf("Test[%d] failed\n",i+1);
            printf("\033[0m");
        }
    }

}


