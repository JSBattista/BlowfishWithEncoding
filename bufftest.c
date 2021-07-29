/********* bufftest.cc **********/
//   From Schnier's blog. Author unknown. 
// to compile and link this version, use
//g++ -Wall bufftest.c Blowfish.c -Wwrite-strings   -o bufftest
//
// compile and link with base64 utility code
//	g++ -Wall bufftest.c Blowfish.c -Wwrite-strings -fpermissive  -o bufftest
// note: minimalist version. 
//
// base64 code from:
//     http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/
//... some minor adaptations.   
//
//	Some other useful information:
//     https://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
//
//
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Blowfish.h"
#include "base64.c"
#include <time.h>
using namespace std;
int main()
{
	Blowfish BF;
	double speed;
	time_t begin,end;
	char *buff;
	buff = new char[48];   // encryption routine requires buffer to be created and allocated like this.
	char *plain =  (char*)"The rain on the plane falls mainly on my brain!!";
	for (int incr = 0; incr < 48; incr++){  // the encryption routine does not tolerate any other way (segfaults)
		buff[incr] = plain[incr];
	}  // for
	begin = time(NULL);
	printf("Before: %s\n", buff);
	BF.Set_Passwd((char*)"xxxxxxxxxxxxxxxx");
	printf("now going to encrypt and base64 encode for transport....\n");
	BF.Encrypt((void *)buff,48);

	size_t encodedlen;
	//printf("encrypted... %s\n", buff);
	unsigned char* encoded;
	encoded =  base64_encode((const unsigned char*)buff, 48, &encodedlen);
	printf("encoded  %i bytes\n", encodedlen);
	printf("after encrypt and encode  %s\n Now going to base64 decode and then decrypt...\n", encoded);




	size_t decodedlen;
	unsigned char* decoded;          
	decoded  = base64_decode((const unsigned char*)encoded, encodedlen, &decodedlen);
	
	printf("decoded %i bytes\n", decodedlen);


	BF.Decrypt((void *)decoded,48);
	printf("decrypted.... %s\n", decoded);
	end = time(NULL);
	speed =  end-begin;
	printf("Total time %i\n", speed);
	return 1;
}
