#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int main(){
    char filename[50];
    int status;

    int t_num = 10;
    int *test_status = malloc(sizeof(int) * t_num);
    system("make clean > /dev/null 2>&1"); // remove old images and tests
    for (int i = 1; i <= t_num ; i++){
        
        FILE *fp = popen("./tested_program/graph_cli > /dev/null 2>&1", "w"); // remove stdbuf -oL

        
        sprintf(filename, "./tests_output/test_%d", i);
        FILE *testfile = fopen(filename, "w");

       if (fp != NULL){
            printf("Test %d STARTED\n", i);

            int r = handle_test_case(fp, i, testfile);

            if (r == 0){
                printf("\033[0;31m"); //red color
                printf("Test %d FINISHED: test resulted in %s\n\n", i, "FAILURE");
                printf("\033[0m");
                fputs("> RESULT\n    FAILURE", testfile);
            }
            else if (r ==1){
                printf("\033[0;32m"); //green color
                printf("Test %d FINISHED: test resulted in %s\n\n", i, "SUCCESS");
                printf("\033[0m");
                fputs("> RESULT\n    SUCCESS", testfile);
            }
            test_status[i-1] = r;
            
            printf("Press Enter to continue");
            while(getchar() != '\n');
            printf("\n");
       }
       fclose(testfile);
       
    
    }
    print_test_status(test_status, t_num);
    
    return 0;
}


