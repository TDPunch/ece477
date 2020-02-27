/* Author: Tyler Punch
 * File: main.c
 * Purpose: Contains main function for testing functions and error checking
 */

#include <stdio.h>
int main(int argc, char *argv[])
{
	char *ptr, *ptr1;

	ptr = "18";
	ptr1 = "2";


	printf("%d\n", sizeof(ptr));
	printf("%c\n", *(ptr1+1));
}
