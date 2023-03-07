#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libsys.h"

#define TREPORT(a1,a2) printf("Status %s: %s\n\n",a1,a2); fflush(stdout);

void process_line( char *test_case );

int main(int argc, char *argv[])
{
	FILE *cfptr;
	char test_case[50];

	if( argc != 2 ){
		fprintf(stderr, "Usage: %s testcasefile\n", argv[0]);
		exit(1);
	}

	cfptr = (FILE *) fopen(argv[1], "r");
	while(fgets(test_case, sizeof(test_case)-1, cfptr)){
		// printf("line:%s",test_case);
		if( !strcmp(test_case,"\n") || !strcmp(test_case,"") )
			continue;
		process_line( test_case );
	}
	return 0;
}


void process_line( char *test_case )
{
//Initialize Valriable 
//Handle testcases for 
//CREATE 
//OPEN 
//ADD_BOOK 
//ADD_STUDENT 
//SEARCH_BOOK_ISBN 
//SERACH_BOOK_TITLE
//SEARCH_STUDENT_NAME 
//DELETE_STUDENT 
//DELETE_BOOK
//ISSUE 

}


