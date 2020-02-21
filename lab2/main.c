/* Author: Tyler Punch
 * Due Date: 02/21/2020
 * File: main.c
 * Purpose: This file contains the main function for lab2.
 */

#include <stdio.h>
#include <unistd.h>
#include "moon_phase.h"

int main(int argc, char *argv[])
{
	FILE *f;
	int c = 0; 
	long int size = 0;
	//long int size = 0;

	//f = get_json();
	//size = get_size(f);
	f = popen("curl wttr.in/?format=j1", "r");
	sleep(3);

	printf("\n");
	
	do {
		c = fgetc(f);
		if(feof(f)) break;
		printf("%c", c);
	} while(1);

	pclose(f);
	return 0;
}
