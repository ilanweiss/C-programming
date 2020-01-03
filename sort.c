#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringList.h"

void *malloc_wrapper(unsigned int);

/*****************
Implements a program similar to the sort command in Linux.

The program should be executed as follows:

./sortFile file key1 [key2 ...]

The first argument is a path to a readable file, and it is followed by a list of positive integers (>0) representing sorting keys. The program should print the lines of the input file to the standard output, sorted in ascending lexicographic order of the words indexed according to the keys. For instance, executing ./sortFile myFile 4 2 will print the lines of myFile sorted primarily according to the lexicographic order of the 4th word in each line, and secondarily according to the lexicographic order of the 2nd word in each line. Lines that are identical in their 4th and 2nd words should be printed according to their order of appearance in the file. [ similar to what sort myFile -k4,4 -k2,2 does ]

* Use dynamic allocation to create the integer array that holds the sort keys.
* Your main function should use a single array variable to read lines using the fgets function (from library stdio). You may assume that lines in the input file have no more than 200 characters (not including the newline).
* You may also assume that the file contains no more than 1,000 lines.
* Each line read from the file should be converted to a string list using function createStrList from your solution to 1.5.
* Use the functions you implemented in 2.3 – 2.5.
* Make sure to free all dynamically allocated memory.
* Instead of a file name, the user may specify “-“ to indicate that lines should be read from the standard input. For instance, sortFile - 4 2.
* Error messages should be printed to standard error.
*****************/

int main(int argc, char **argv) {
   // check if user input is correct
   // Not enough arguments
   if (argc < 3) {
      fprintf(stderr, "Usage: ./sortFile file key1 [key2 ... ]\n");
      return 1;
   }
   FILE* fp = (strcmp(argv[1], "-") == 0) ? stdin : fopen(argv[1],"r");
   int *keys = malloc_wrapper(4 * (argc - 2));
   // Providing non-existing file, or file with no read permissions
   if (fp == NULL) {
      fprintf(stderr, "Could not open input file %s for reading\n", argv[1]);
      return 1;
   }
   int i, currKey;
   // Put user's keys into arr
   for (i = 2; i < argc; i++) {
    currKey = string2posInt(argv[i]);
    // Check for bad indices
    if ( currKey == 0) {
       fprintf(stderr, "key %s is not a positive integer\n", argv[i]);
       return 1;
    }
    keys[i-2] = currKey;
  }
   int curr_line = 0;
   char *line = malloc(200);
   char **strArr = malloc( sizeof(char*) * 1000);
   while( fgets(line, 201, fp) ){
      strArr[curr_line] = createStrList(line);
      curr_line++;
      }
   free(line);
   strListSort(strArr, curr_line, keys, argc - 2);
   printStrLists(strArr, curr_line);
   for (i = 0; i < curr_line; i++)
      free(strArr[i]);
   free(keys);
   return 0;
}
                                       
