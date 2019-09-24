/* 
Authors: Darren, Wei Cheng
File Name: statsum.c 
All Files: statsum.c, statsumhdr.h, statsumsrc.c 
To compile (without gdb), type "gcc statsum.c statsumsrc.c -o statsum -Wall" */ 

/* references 
Certain algorithms have been adapted/modified from the following sites: 
1. Read from file into linked list - https://stackoverflow.com/questions/25746255/linked-list-in-c-read-from-file
2. Read tab-separated integers in c - https://stackoverflow.com/questions/5357184/how-to-read-in-a-text-file-of-tab-separated-integers-in-c
3. Read files separated by tabs in c - https://stackoverflow.com/questions/29476556/read-files-separated-by-tab-in-c
4. Expand array with realloc inside function - https://stackoverflow.com/questions/26368022/expand-an-array-with-realloc-inside-of-a-function-pointers
5. qSort - http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
6. String tokenization - //www.tutorialspoint.com/c_standard_library/c_function_strtok.htm */ 

/* learning resources
Learning resources and related notes were read from the following sites:
1. Read tab delimiters to struct - https://stackoverflow.com/questions/27503904/read-tab-delimited-file-to-structure-in-c
2. Linked list basics - https://www.tutorialspoint.com/data_structures_algorithms/linked_list_algorithms.htm
3. Linked list implementation - https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
4. Read file into array of structs - http://www.wellho.net/resources/ex.php4?item=c209/lunches.c
5. Read words from file into node struct in c - https://stackoverflow.com/questions/26491467/read-words-from-file-into-node-struct-in-c
6. Read from file into structure - https://stackoverflow.com/questions/11280523/c-reading-from-file-into-structure
7. Bubble sort - http://www.sanfoundry.com/c-program-sorting-bubble-sort/
8. Sort array - https://en.wikiversity.org/wiki/C_Source_Code/Sorting_array_in_ascending_and_descending_order
9. qSort - https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm 
10. Compile - https://stackoverflow.com/questions/8728728/compiling-multiple-c-files-in-a-program */ 

// import the libraries 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "statsumhdr.h"

// main function
int main(){
	
	// declare and/or initialize global variables
	char val[1];
	double malestats[6] = {0}, femalestats[6] = {0};
	FILE *fp = NULL; 
	survMRlts *survMRltsPtr = (survMRlts *)malloc(RLTS_SIZE * sizeof(survMRlts)); 
	survFRlts *survFRltsPtr = (survFRlts *)malloc(RLTS_SIZE * sizeof(survFRlts)); 
	
	// retrieve file content 
	fp = fopen("psuedo_facebook.tsv","r");
	storeRetrFileContent(val, fp, &survMRltsPtr, &survFRltsPtr, malestats, femalestats); // function: validate and store retrieved file content 
	if(val[0] == 'f'){return(-1);}
	fclose(fp);
	
	// function: highest likes received count 
	highestLikes(malestats, 'm', survMRltsPtr, survFRltsPtr); 
	highestLikes(femalestats, 'f', survMRltsPtr, survFRltsPtr); 
	
	// function: lowest likes received count 
	lowestLikes(malestats, 'm', survMRltsPtr, survFRltsPtr); 
	lowestLikes(femalestats, 'f', survMRltsPtr, survFRltsPtr); 
	
	// function: total likes received count 
	totalLikes(malestats, 'm', survMRltsPtr, survFRltsPtr); 
	totalLikes(femalestats, 'f', survMRltsPtr, survFRltsPtr); 
	
	// function: average likes received count 
	avgLikes(malestats);  
	avgLikes(femalestats); 
	
	// function: median likes received count 
	medianLikes(malestats, 'm', survMRltsPtr, survFRltsPtr); 
	medianLikes(femalestats, 'f', survMRltsPtr, survFRltsPtr); 
	
  // print statistics 
  printf("Statistic Summary\n"); 
  printf("%sMale users\n%s", green, reset); 
  prStatistics(malestats);	// function: print statistics 
  printf("%sFemale users\n%s", magenta, reset);  
  prStatistics(femalestats); // function: print statistics
	
	// free the memory 
	free(survMRltsPtr);
	free(survFRltsPtr);
	
	return 0;
}