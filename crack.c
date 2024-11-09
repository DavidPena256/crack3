#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#include "md5.h"

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
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
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    
    // TODO
    // Open the password file for reading.
    int count = 0;
    char line[1000];
    while(fgets(line, 1000, passwordFile)){
        
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        char *hashedPass = md5(line, strlen(line));

        char *foundHash = substringSearchAA(hashedPass, hashes, size);
        if (foundHash){
            printf("Password: %s\tHash: %s\n", line, hashedPass);
            count += 1;
        }
    }
    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search.

    // TODO
    // When done with the file:
    //   Close the file
    //   Display the number of hashes found.
    //   Free up memory.
    fclose(hashFile);
    fclose(passwordFile);
    printf("Number of hashes found: %d out of %d\n", count, size);
    freeAA(hashes, size);
}
