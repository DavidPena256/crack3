#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#include "md5.h"

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int strcomp(const void *a, const void *b){

    char **aa = (char **)a;
    char **bb = (char **)b;

    return strcmp(*aa, *bb);
}

int strsearch(const void * target, const void *elem){

    char *tt = (char *) target;
    char **ee = (char **)elem;

    return strcmp(tt, *ee);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    FILE *hashFile = fopen(argv[1], "r");
    if (!hashFile){
        printf("Can't open hash file.\n");
        exit(1);
    }
    
    FILE *passwordFile = fopen(argv[2], "r");
    if (!passwordFile){
        printf("Can't open password File,\n");
        exit(1);
    }
    
    int size;
    char **hashes = loadFileAA(argv[1], &size);
    
    qsort(hashes, size, sizeof(char *), strcomp);
    
    int count = 0;
    char line[1000];
    while(fgets(line, 1000, passwordFile)){
        
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';
        
        char *hashedPass = md5(line, strlen(line));

        char *foundHash = bsearch(hashedPass, hashes, size, sizeof(char *), strsearch);
        if (foundHash){
            printf("Password: %s\tHash: %s\n", line, hashedPass);
            count += 1;
        } 
    }

    //   Close the file
    //   Display the number of hashes found.
    //   Free up memory.
    fclose(hashFile);
    fclose(passwordFile);
    printf("Number of hashes found: %d out of %d\n", count, size);
    freeAA(hashes, size);
}
