/********* BFtest.cc **********/
//   From Schnier's blog. Author unknown. 
// to compile and link this version, use
//		g++ -Wall bftest.c Blowfish.c -Wwrite-strings   -o bftest
//
//
//
//
//
//
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Blowfish.h"
#define BUFF_SIZE 1048576  // 1MB
#define NUM_TRIALS 100
int Test(Blowfish *);
double Speed(Blowfish *);
using namespace std;
int main()
{
	int result;
	double speed;
	Blowfish BF;
	cout << "Blowfish verification: ";
	if ((result = Test(&BF)))
	{
		cout << "\aFailed " << (result>0?"en":"de") << "crypting test vector " <<
		abs(result) << endl;
		return 0;
	}
	else
		cout << "Passed" << endl;
	printf("result variable is %i\n", result);
	if ((speed = Speed(&BF)) <= 0)
		cout << "Not enough time elapsed for the test, or something funny happend." << 	endl;
	else
		cout << "The throughput is " << speed << "MB/s" << endl;
	return 1;
}
int Test(Blowfish *BF)
{
	DWord Test_Vect;
	char *Passwd[2] = {(char*)"abcdefghijklmnopqrstuvwxyz",(char*)"Who is John Galt?"};
	unsigned int Clr0[2] = {0x424c4f57,0xfedcba98};
	unsigned int Clr1[2] = {0x46495348,0x76543210};
	unsigned int Crypt0[2] = {0x324ed0fe,0xcc91732b};
	unsigned int Crypt1[2] = {0xf413a203,0x8022f684};
	for (unsigned int i=0;i<2;i++)
	{
		Test_Vect.word0.word = Clr0[i];
		Test_Vect.word1.word = Clr1[i];
		BF->Set_Passwd(Passwd[i]);
		BF->Encrypt((void *)&Test_Vect,8);
		if ((Test_Vect.word0.word != Crypt0[i]) || (Test_Vect.word1.word != Crypt1[i]))
			return (i+1);
		BF->Decrypt((void *)&Test_Vect,8);
		if ((Test_Vect.word0.word != Clr0[i]) || (Test_Vect.word1.word != Clr1[i]))
			return -(i+1);
	}
	return 0;
}
double Speed(Blowfish *BF)
{
	char *buff;
	unsigned int i;
	time_t begin,end;
	buff = new char[BUFF_SIZE];
	if (buff == NULL)
	{
		cerr << "\aRan out of memory for the test buffer\n";
		return 0;
	}
	srand(0);
	for (i=0;i<BUFF_SIZE;i++)
		buff[i] = rand()%256;
	BF->Set_Passwd((char*)"ianchan");

	begin = time(NULL);
	for (i=0;i<NUM_TRIALS;i++)
		BF->Encrypt((void *)buff,BUFF_SIZE);
	end = time(NULL);
	delete []buff;
	if (end-begin < 1)
		return 0;
	else
		return double(NUM_TRIALS)/(end-begin);
}
