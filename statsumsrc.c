/* 
Authors: Darren, Wei Cheng
File Name: statsumsrc.c 
All Files: statsum.c, statsumhdr.h, statsumsrc.c 
To compile (without gdb), type "gcc statsum.c statsumsrc.c -o statsum -Wall" */  

// import the libraries 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "statsumhdr.h" 

/* function: validate and store retrieved file content 
Validate the entries and store the retrieved file content from the file into the survRlts structs.
Input Parameter(s):	input file, survMRlts struct pointer, survFRlts struct pointer, male stats array, female stats array 
Return Value:				- */ 
char storeRetrFileContent(char *val, FILE *fp, survMRlts **survMRltsPtr, survFRlts **survFRltsPtr, double *malestats, double *femalestats){ 
	
	// declare and/or initialize variables 
	char gender, entry[ENTRY_SIZE], entry2[ENTRY_SIZE], *token, *token2;
	int i=-2, im=-1, ig=-1, c, j;
	
	// validate if input file exists 
	if(fp == NULL){
  	printf("The file does not exist.\n");
		return val[0] = 'f';
		
	// validate file content 
	}else{
		
		while(fgets(entry,ENTRY_SIZE,fp)){
			
			// declare and/or initialize variables 
			i++,j=1;
			strcpy(entry2,entry);
			token = strtok(entry, "\t"); 
			char condition = 'F'; 
			
			// if non-header entry 
			if(i>-1){
		
				// validate the entry
				// case a - age below 13 or above 90 
				token = strtok(NULL, "\t");
				if((atoi(token) < 13) || (atoi(token) > 90)){condition = 'T';}
				
				// case b - day not between 1-31
				token = strtok(NULL, "\t"); 
				if((atoi(token) < 1) || (atoi(token) > 31)){condition = 'T';}
				
				// case c - month not between 1-12 
				for(c=0; c<2; c++){token = strtok(NULL, "\t");}
				if((atoi(token) < 1 ||  (atoi(token)) > 12)){condition = 'T';}
				
				// case d - gender does not contain 'Male' or 'Female'
				token = strtok(NULL, "\t");
				if((strncmp(token, "male", strlen("male")) != 0) && (strncmp(token, "female", strlen("female")) != 0)){condition = 'T';}
				else if(strncmp(token, "male", strlen("male")) == 0){gender='m';}
				else{gender='f';}
				
				// case e - likes received not greater than 0 
				for(c=0; c<5; c++){token = strtok(NULL, "\t");}
				if(atoi(token) <= 0){condition = 'T';} 

				// entry validated, store entry
				token2 = strtok(entry2, "\t");
				if(condition == 'F'){
					
					// assign struct based on gender 
					switch(gender){
						case 'm': im++, malestats[0]++; break;
						case 'f': ig++, femalestats[0]++; break; 
					}

					// reallocate memory if not enough 
					if(im == RLTS_SIZE){*survMRltsPtr = realloc(*survMRltsPtr, (RLTS_SIZE*2) * sizeof(survMRlts));}
					if(ig == RLTS_SIZE){*survFRltsPtr = realloc(*survFRltsPtr, (RLTS_SIZE*2) * sizeof(survFRlts));}

					// write onto struct 
					while(token2!=NULL){
						switch(j){
							// userid 
							case 1: 
								switch(gender){
									case 'm': (*survMRltsPtr+im)->userid = atoi(token2); break;
									case 'f': (*survFRltsPtr+ig)->userid = atoi(token2); break;
								}
								for(c=0; c<10; c++){token2 = strtok(NULL, "\t");}
								break; 
							// likes_received 
							case 2:
								switch(gender){
									case 'm': (*survMRltsPtr+im)->likes_received = atoi(token2); break;
									case 'f': (*survFRltsPtr+ig)->likes_received = atoi(token2); break; 
								}
								for(c=0; c<5; c++){token2 = strtok(NULL, "\t");}
								break;
						}
						j++;
					} 
				} 
			} 
		} 
		return 0; 
	}
}

/* function: highest likes received count 
Retrieve the highest likes.
Input Parameters(s):	male OR female stats array, gender, survMRlts array, survFRlts array 
Return Value:					- */ 
void highestLikes(double *genderstats, char gender, survMRlts *survMRltsPtr, survFRlts *survFRltsPtr){
	
	// declare and initialize variables
	int i;
	
	// retrieve highest likes 
	for(i=0; i<genderstats[0]; i++){
		if(gender == 'm' && (((survMRltsPtr+i)->likes_received) > genderstats[1])){
			genderstats[1] = (survMRltsPtr+i)->likes_received;
		}else if(gender == 'f' && (((survFRltsPtr+i)->likes_received) > genderstats[1])){
			genderstats[1] = (survFRltsPtr+i)->likes_received;
		}
	}
}

/* function: lowest likes received count 
Retrieve the lowest likes. 
Input Parameters(s):	male OR female stats array, gender, survMRlts array, survFRlts array 
Return Value:					- */ 
void lowestLikes(double *genderstats, char gender, survMRlts *survMRltsPtr, survFRlts *survFRltsPtr){
	
	// declare/or and initialize variables
	int i;
	switch(gender){
		case 'm': genderstats[2] = survMRltsPtr->likes_received; break;
		case 'f': genderstats[2] = survFRltsPtr->likes_received; break; 
	}
	
	// debug feature 
	#ifdef DEBUG
	printf("%sFirst occurence of number of likes:\n%d\n\n", yellow, genderstats[2]);
	#endif
	
	// retrieve lowest likes 
	for(i=0; i<genderstats[0]; i++){
		if(gender == 'm' && (((survMRltsPtr+i)->likes_received) < genderstats[2])){
			genderstats[2] = (survMRltsPtr+i)->likes_received;
		}else if(gender == 'f' && (((survFRltsPtr+i)->likes_received) < genderstats[2])){
			genderstats[2] = (survFRltsPtr+i)->likes_received;
		}
	}
}

/* function: total likes received count 
Calculate the total likes. 
Input Parameters(s):	male OR female stats array, gender, survMRlts array, survFRlts array 
Return Value:					- */ 
void totalLikes(double *genderstats, char gender, survMRlts *survMRltsPtr, survFRlts *survFRltsPtr){
	
	// declare and/or initialize variables 
	int i; 
	
	// calculate total likes 
	for(i=0; i<genderstats[0]; i++){
		switch(gender){
			case 'm': genderstats[3] += (survMRltsPtr+i)->likes_received; break; 
			case 'f': genderstats[3] += (survFRltsPtr+i)->likes_received; break; 
		}
	}
}

/* function: average likes received count 
Calculate the average likes.
Input Parameters(s):	male OR female stats array
Return Value:					- */ 
void avgLikes(double *genderstats){
	genderstats[4] = genderstats[3] / genderstats[0]; 
}

/* function: qsort (male) / qsort (female)
Sorts the array of structs in ascending order of likes_received.
Input Paramter(s):	void *a, void *b 
Return Value:				comparison  */ 
int maleCmp(const void *a, const void *b) { 
		survMRlts *ia = (survMRlts *)a; 
		survMRlts *ib = (survMRlts *)b; 
    return (ia->likes_received - ib->likes_received);
} 

int femaleCmp(const void *a, const void *b){
		survFRlts *ia = (survFRlts *)a; 
		survFRlts *ib = (survFRlts *)b; 
    return (ia->likes_received - ib->likes_received);
}

/* function: median likes received count 
Retrieve the median of the likes. 
Input Parameter(s):	male OR female stats array, gender, survMRlts array, survFRlts array 
Return Value:				- */
void medianLikes(double *genderstats, char gender, survMRlts *survMRltsPtr, survFRlts *survFRltsPtr){
	
	// declare and/or initialize variables 
	int i; 
	
	// sort the structs based on ascending likes 
	switch(gender){
		case 'm': qsort(survMRltsPtr, genderstats[0], sizeof(survMRlts), maleCmp); break;
		case 'f': qsort(survFRltsPtr, genderstats[0], sizeof(survFRlts), femaleCmp); break; 
	}
	
	// retrieve the median likes 
	if((int)genderstats[0] % 2 == 0){
		i = (genderstats[0]/2); 
		switch(gender){
			case 'm': genderstats[5] = (((survMRltsPtr+i-1)->likes_received)+((survMRltsPtr+i)->likes_received))/2; break;
			case 'f': genderstats[5] = (((survFRltsPtr+i-1)->likes_received)+((survFRltsPtr+i)->likes_received))/2; break; 
		}
	}else{
		i = ((genderstats[0]-1)/2);
		switch(gender){
			case 'm': genderstats[5] = (survMRltsPtr+i)->likes_received; break; 
			case 'f': genderstats[5] = (survFRltsPtr+i)->likes_received; break; 
		}
	} 
}

/* function: print statistics 
Print the statistics for male and female users.
Input Parameter(s):	male OR female stats array 
Return Value:				- */ 
void prStatistics(double *genderstats){
	printf("Valid entries count: 		%d\n",(int)genderstats[0]); 
  printf("Highest likes received count:	%d\n",(int)genderstats[1]); 
  printf("Lowest likes received count:	%d\n",(int)genderstats[2]); 
  printf("Likes received count total:	%d\n",(int)genderstats[3]); 
  printf("Likes received count average:	%.2f\n",genderstats[4]); 
  printf("Likes received count median:	%d\n\n",(int)genderstats[5]);
}
