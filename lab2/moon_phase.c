/* Author: Tyler Punch
 * Due Date: 02/21/2020
 * File: moon_phase.c
 * Purpose: This file contains functions relating finding the phase of the moon from a * file (Part A). Also the something cool I did (Part B).
 */

#include <stdio.h>
#include <unistd.h>
#include "moon_phase.h"

// Uses curl command to get file pointer for a given URL.
// Returns NULL on error
FILE *get_json(void)
{
	//char curl_command[] = "curl wttr.in/?format=j1";
	//char curl_type[] = "r";
	FILE *f;

//	printf("%s", curl_command);
	f = popen("curl 'wttr.in/?format=j1'", "r");

	if (f == NULL) {
		fprintf(stderr, "Could not open URL\n");
		return NULL;
	}

	return f;
}

// Gets size of the JSON file found by get_json()
// Returns -1 on error, file size on success
long int get_size(FILE *f)
{
	long int file_size = 0;
	int err = 0;

	if (f == NULL) {
		fprintf(stderr, "Invalid file pointer\n");
		return -1;
	}
	
	// Find the end of the file, then check for errors
	err = fseek(f, 0, SEEK_END);
	if (err < 0) {
		fprintf(stderr, "Could not get file size");
		return -1;
	}

	// Get size of the file, then reset file pointer
	file_size = ftell(f);
	rewind(f);

	return file_size;
}
