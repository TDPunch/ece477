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

	f = get_json();
	err = find_phase(f);

	return 0;
}
