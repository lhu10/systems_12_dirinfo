#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv){

    DIR *d; 
    struct dirent *entry; 
    struct stat sb; 
    char input[100]; 
    
    if(argv[1] != NULL){
        strncpy(input, argv[1], sizeof(input)-1);
    }
    else{
        printf("Input a directory to scan: ");
        scanf("%s", input);
    }

    d = opendir(input); 
    if(d == NULL){
        printf("Error %d: %s\n", errno, strerror(errno));
        return -1; 
    }

    entry = readdir(d);

    printf("Statistics for directory: %s\n", input);
    
    int total_size; 
    total_size = 0; 
    while(entry != NULL){
        if(entry->d_type == DT_REG){
            stat(entry->d_name, &sb); 
            total_size += sb.st_size;
        }
        entry = readdir(d);
    }

    printf("Total Directory Size: %d Bytes\n", total_size);

    rewinddir(d);
    entry = readdir(d);
    
    printf("Directories:\n"); 
    while(entry != NULL){
        if(entry->d_type == DT_DIR){
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }

    rewinddir(d);
    entry = readdir(d);

    printf("Regular files:\n");
    while(entry != NULL){
        if(entry->d_type == DT_REG){
            printf("\t%s\n", entry->d_name);
        }
        entry = readdir(d);
    }
    
    closedir(d);

    return 0; 
}
