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
	int err;

//	Part A
//	f = get_json();
//	err = find_phase(f);

//  Part B	
	f = get_json();
	err = something_cool(f);

	if (err < 0) {
		fprintf(stderr, "Error in something_cool()");
		return -1;
	}

	f = get_json();

	if (argc == 2) {
		err = print_answer(argv[1], f);
		if (err < 0) {
			fprintf(stderr, "Error in print_answer");
			return -1;
		}
	}

	return 0;
}
