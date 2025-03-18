#include <stdio.h>

#define PATH_MAX 30


int main(){
    fprintf(stderr, "d");
    FILE *fp = popen("stdbuf -oL ./graph_cli", "w");
    int status;
    char path[PATH_MAX];
    
    
    
    if (fp == NULL)
        /* Handle error */;
        
    
    fgets(path, PATH_MAX, fp);
        printf("%s", path);

    fprintf(stderr, "d");

    fprintf( fp, "2\n");
    
    
    
    status = pclose(fp);
    if (status == -1) {
        /* Error reported by pclose() */
        
    } else {
        /* Use macros described under wait() to inspect `status' in order
           to determine success/failure of command executed by popen() */
        
    }
    return 0;
}
