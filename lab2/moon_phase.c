/* Author: Tyler Punch
 * Due Date: 02/21/2020
 * File: moon_phase.c
 * Purpose: This file contains functions relating to 
 * finding the phase of the moon from a file (Part A). 
 * Also the something cool I did (Part B).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "moon_phase.h"

// Uses curl command to get file pointer for a given URL.
// Returns NULL on error, file pointer on success.
FILE *get_json(void)
{
	FILE *f;

	// Run curl command on designated URL
	f = popen("curl wttr.in/?format=j1", "r");

	// Give curl a second to get the whole URL
	sleep(1);

	// Check for errors
	if (f == NULL) {
		fprintf(stderr, "Could not open URL\n");
		return NULL;
	}

	printf("\n");

	return f;
}

// Use file pointer from get_json() to find the data field containing the
// phase of the moon and print it by calling print_phase().
// Returns -1 on error, 0 on success.
int find_phase(FILE *f)
{
	char *str = NULL, *out = NULL, *err;
	int err_int = 0;

	// Allocate some memory for the string buffer followed by some
	// standard error checking.
	// MAX_LINE_SIZE is 80 which is long enough to get a string 
	// containing a phase of the moon (engineering design choice).
	str = (char *)malloc(MAX_LINE_SIZE);
	if (str == NULL) {
		fprintf(stderr, "Error, memory allocation failed\n");
		return -1;
	}

	// Iterate through the file (command line output) until 
	// the phase of the moon has been found, then print.
	do {
		err = fgets(str, MAX_LINE_SIZE, f);
		if (err == NULL) {
			fprintf(stderr, "Error or End-of-File reached\n");
			return -1;
		}
		//printf("%s", str);
		out = strstr(str, "moon_phase");
		if (out != NULL) {
			print_phase(out);
			break;
		}
	} while(1);

	// Deallocate the memory
	free(str);

	// Close the process
	err_int = pclose(f);
	if (err_int < 0) {
		fprintf(stderr, "Error, failed to close process\n");
		return -1;
	}

	return 0;
}

// print_phase() prints the phase of the moon when found by find_phase()
// This function returns void becuase error checking is done in find_phase()
void print_phase(char *str)
{
	// Skip to actual phase of the moon by bypassing a few quotes
	while (*str != ':') str++;
	while (*str != '"') str++;

	while (*str != '\n') {
		// Skip string "moon_phase"
		//while (*str != '"') str++;
		// Remove extraneous characters and print
		if ((*str >= 'A' && *str <= 'Z') || (*str >= 'a' && *str <= 'z')) {
			printf("%c", *str);
			str++;
		}
		else if (*str == ' ') {
			printf("%c", *str);
			str++;
		}
		else str++;
	}
	printf("\n");
}
