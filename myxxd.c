#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

/**
 * Parses the command line.
 *
 * argc: the number of items on the command line (and length of the
 *       argv array) including the executable
 * argv: the array of arguments as strings (char* array)
 * bits: the integer value is set to TRUE if bits output indicated
 *       outherwise FALSE for hex output
 *
 * returns the input file pointer (FILE*)
 **/
FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }

  if (argc == 2 &&
      (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  } else {
    *bits = FALSE;
  }

  return stdin;
}

/**
 * Writes data to stdout in hexadecimal.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsHex(unsigned char *data, size_t size) {
  
	int i;
	int hexdump;
 	
	printf(" ");
	for(i = 0; i < size; i++){

		hexdump = data[i];

		printf("%02x",hexdump);

		if(i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 11 || i == 13){
	
			printf(" ");
	
		}

	}
	
	if(size < 16){
	
		int t = 16 - size;
		
		if(t % 2 == 1){

		for(i = 0; i < t; i++){
		
			printf("  ");

			if(i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 11 || i == 13){

                        printf(" ");

               		}

		}

		}
	
		else{
		
		for(i = 0; i < t; i++){
		
			printf("  ");

			if(i == 2 || i == 4 || i == 6 || i == 8 || i == 10 || i == 12 || i == 14){
			
				printf(" ");
			
			}
		
		}
		
		
		}


	}

}

/**
 * Writes data to stdout as characters.
 *
 * See myxxd.md for details.
 *
 * data: an array of no more than 16 characters
 * size: the size of the array
 **/
void printDataAsChars(unsigned char *data, size_t size) {

	int i;
	
	for(i = 0; i < size; i++){
	     if(data[i] == '\n'){
		
			data[i] = '.';
			
	     }

	     if(data[i] < 32){
	     
	     	data[i] = '.';

	     }
		printf("%c",data[i]);
	
	}
	
}

void printDataAsBinary(unsigned char *data, size_t size){

	int i;
	int t;
	int j;
	int w;
	int a[8];
	
	

	 for(i = 0; i < size; i++){


	  t = data[i];
       	   
	 	for(j = 0; j < 8; j++){

	  		if(t % 2 == 1){
	   			a[7 - j] = 1;
	  		}

	  		else{
	        		a[7 - j] = 0;
	  		}
	  	t = t / 2;
	  	
	 	}

		for(w = 0; w < 8; w++){
			printf("%d",a[w]);
		}

		printf(" ");

	 }

	if(size < 6){
	
		int s = 6 - size;

		for(i = 0; i < s; i++){
		
			printf("        ");

			printf(" ");
		
		}
	
	
	}


}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

/**
 * Bits output for xxd.
 *
 * See myxxd.md for details.
 *
 * input: input stream
 **/
void readAndPrintInputAsBits(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data ,1, 6, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printf(" ");
    printDataAsBinary(data,numBytesRead);
    printf(" ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 6, input);
  }
}

int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
