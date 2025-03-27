#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com.h" 
#include "parser.h"

int handle_test_case(FILE * fp, int opt, FILE  * testfile){
    int result = 0; // success or failure of the test

    // buffer 
    char line[125];
    char req[250] = "";

    // graph characteristics 
    int e; // edges number
    int n; // nodes number
    int t; // type
    int d; // direction

    int n1, n2;
    int s = 0;

    // type distinction : 1 - manually written
    //                    2 - randomly generated
    //                    3 - made with llm

    FILE *exp_out; // expected output, used for checking correctness of edges
    
    // 10 cases where 1-5 are manual added edges, 6-8 random graphs, 9-10 graphs made with llm

    char casefile[30];
    sprintf(casefile, "./input/case%d", opt);
    FILE *cs = fopen(casefile, "r");

    if (cs == NULL){
        printf("Error opening a case file\n");
        return result;
    }

    fgets(line, sizeof(line), cs);
    if (sscanf(line, "%d, %d, %d, %d", &e, &n, &t, &d) != 4){
        printf("Error reading from a case file\n");
        return result;
    }
    if (t == 3 ){
        fgets(req, sizeof(req), cs);
        puts(req);
    }
    if (t != 3)
        exp_out = manual_mode(opt, e, n, fp, t, d);

    



    
    

    // print on stdin and write into a file info about graph characteristics depending on the type of graph (1-3)
    add_entry(testfile, "> DETAILS\n");

    add_entry(testfile, "    Enabled '%s'\n", t != 3 ? "manual parameters input" : "chat mode");

    

    if (t != 3){
        add_entry(testfile, "    Enabled '%s'\n", t == 1 ? "manual edge input" : "Random graph");
        
    } else 
        add_entry(testfile, "    Requested: %s\n", req);    // spaces are for readability

    add_entry(testfile, "    Enabled '%s' graph type\n", d == 1 ? "Directed" : "Undirected");
    
    add_entry(testfile, "    Asked for %d nodes\n", n);
    
    add_entry(testfile, "    Asked for %d edges\n", e);
    


    if (t == 1){
        while (fgets(line, sizeof(line), cs)){
            //puts(line);
            if ( sscanf(line, "%d %d %d", &n1, &n2, &s) > 1){
                add_edge(fp, exp_out, n1, n2, d, s);
                add_entry(testfile,"    Asked for edge %d %d\n", n1, n2);
            }
            else {
                //printf("%d %d\n", n1,n2);
                printf("Error reading an edge input\n");
                return result;
            }
        }
    }
    
    // send request to llm and wait for response
    if (t == 3){
        llm_mode(fp, req);
        printf("    Waiting for AI response...\n");
        while (strstr(line, "Raw response:")){
            fgets(line, sizeof(line), fp);
        }
    }

    // save test through a program and open that test
    static char test_output[50];
    strcpy(test_output, save_test(fp, opt));
    pclose(fp); // close tested program 

    FILE *out = fopen(test_output, "r");
    if (out == NULL && t == 3){
        add_entry(testfile, "    (!)Error: Connection to LLM failed\n");
        return result;
    }
    else if (out == NULL){
        printf("Error opening test file\n");
        return result;
    }

    char copy_image[100];
    sprintf(copy_image, "cp %s.png ./output/current_test_diagram.png ", test_output);
    system(copy_image); 
    add_entry(testfile, "> PROGRAM OUTPUT\n");

    if (t == 1){
        fprintf(exp_out, "}\n");
        if (exp_out == NULL){
            add_entry(testfile, "    (!)Error: Generation of expected_ouput file failed\n");
        }
        
        
        fclose(exp_out);
        char filename[50];
        sprintf(filename, "./input/in%d.txt", opt);
        FILE *exp_out = fopen(filename, "r");
        result = compare_files(out, exp_out, test_output);
        fclose(exp_out);
        fclose(out);
        out = fopen(test_output, "r");
        if (out == NULL){
            printf("Error opening test file\n");
            return result;
        }
        while (fgets(line, sizeof(line), out))
            add_entry(testfile, "    %s",line);
        
    }
    
    else if (t == 2 || t == 3){
            result = analyze_graph( e, n, out, d, testfile);
            
    }
    fclose(out);
    
    char open_image[100];
    sprintf(open_image, " xdg-open ./output/current_test_diagram.png &");
    system(open_image); //display image
    
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


