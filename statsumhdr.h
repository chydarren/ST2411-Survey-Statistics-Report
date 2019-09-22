/* 
Authors: Darren, Wei Cheng
File Name: statsumhdr.h
All Files: statsum.c, statsumhdr.h, statsumsrc.c 
To compile (without gdb), type "gcc statsum.c statsumsrc.c -o statsum -Wall" */ 

// definitions
#define RLTS_SIZE 45000 
#define ENTRY_SIZE 300 
#define green "\x1b[32m"
#define magenta "\x1b[35m"
#define yellow "\x1b[33m"
#define reset "\x1b[0m"

// struct: male survey results 
typedef struct sMRlts{
	int userid, likes_received;
} survMRlts;

// struct: female survey results 
typedef struct sFRlts{
	int userid, likes_received;
} survFRlts; 

// function prototypes
char storeRetrFileContent(char * , FILE * , survMRlts ** , survFRlts ** , double * , double * );
int maleCmp(const void *a, const void *b); 
int femaleCmp(const void *a, const void *b); 
void highestLikes(double * , char , survMRlts * , survFRlts * );
void lowestLikes(double * , char , survMRlts * , survFRlts * );
void totalLikes(double * , char , survMRlts * , survFRlts * );
void avgLikes(double * ); 
void medianLikes(double * , char , survMRlts *, survFRlts *); 
void prStatistics(double * );



