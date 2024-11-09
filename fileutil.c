#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	int capacity = 10;
	*size = 0;
	// Allocate memory for an array of strings (arr).
	char ** arr = malloc(capacity * sizeof(char *));
	// Read the file line by line.
	char line[1000];
	while (fgets(line, 1000, in)){
		
		char *nl = strchr(line, '\n');
		if (nl) *nl = '\0';

		if (*size == capacity){
			
			capacity += capacity / 2;
			arr = realloc(arr, capacity * sizeof(char *));

		} 

		arr[*size] = malloc(strlen(line) + 1);
		strcpy(arr[*size], line);
		(*size)++;
	}
	
	fclose(in);
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	
	for (int i = 0; i < size; i++){
		
		int foundString = strcmp(lines[i], target);
		if (!foundString){
			return target;
		}

	}
	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for (int i = 0; i < size; i++){
		free(arr[i]);
	}
	free(arr);
}