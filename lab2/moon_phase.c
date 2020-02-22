/* Author: Tyler Punch
 * Due Date: 02/21/2020
 * File: moon_phase.c
 * Purpose: This file contains functions relating finding the phase of the moon from a * file (Part A). Also the something cool I did (Part B).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "moon_phase.h"

// Uses curl command to get file pointer for a given URL.
// Returns NULL on error
FILE *get_json(void)
{
	FILE *f;
	int c = 0;

	f = popen("curl wttr.in/?format=j1", "r");

	// Give curl a second to get the whole URL
	sleep(1);

	// Check for errors
	if (f == NULL) {
		fprintf(stderr, "Could not open URL\n");
		return NULL;
	}

	printf("\n");

	/*
	do {
		c = fgetc(f);
		if (feof(f)) break;
		printf("%c", c);
	} while(1);*/

	//rewind(f);

	return f;
}	

int print_phase(FILE *f)
{
	char *str = NULL, *out = NULL;
	char *err;
	int i = 0;

	str = (char *)malloc(SIZE_MOON_PHASE);

	do {
		err = fgets(str, SIZE_MOON_PHASE, f);
		if (err == NULL) {
			fprintf(stderr, "Error or End-of-File reached\n");
			return -1;
		}
		//printf("%s", str);
		out = strstr(str, "moon_phase");
		if (out != NULL) {
			while (*out != '\n') {
				printf("%c", *out);
				out++;
			}

			printf("\n");
			break;
		}
	} while(1);

	free(str);

	pclose(f);

	return 0;
}
