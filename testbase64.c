//
//
//
// to compile and link use the following command line.
//	g++  testbase64.c base64.c  -Wall -Wwrite-strings -fpermissive  -o testbase64
//
//
//
//
#include "base64.h"
#include <stdio.h>


int main(){

	const char* testchar = "Hey now!";
	size_t encodedlen;
	printf("%s\n", testchar);
	unsigned char* encoded;
	encoded =  base64_encode(testchar, 8, &encodedlen);
	printf("%s bytes %i\n", encoded, encodedlen);

	size_t decodedlen;
	unsigned char* decoded;          
	decoded  = base64_decode(encoded, encodedlen, &decodedlen);
	printf("%s bytes %i\n", decoded, decodedlen);





	return 0;
}
/*
Output will be:
Hey now!
SGV5IG5vdyE=
 bytes 13
Hey now! bytes 8
*/
