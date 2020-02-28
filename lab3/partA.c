/* Author: Tyler Punch
 * File: partA.c
 * Purpose: This file contains functions to get the 'linux load average'
 * for Part A of Lab 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "gpio.h"

void setup_gpio(void) 
{
	int check = 0, err = 0;

	char arr[16] = {'0', '\0', '1', '\0', '2', '\0', '3', '\0',
					'4', '\0', '5', '\0', '6', '\0', '7', '\0'};
	char *gpio_arr[8];

	// Generate array of string pointers for GPIO0-7
	for(int i = 0; i < 8; i++) {
		gpio_arr[i] = arr + 2*i;
	}

	// Enable GPIOs
	for(int i = 0; i < 8; i++) {
		check = check_export(gpio_arr[i]);
		if (check < 0) {
			err = export_gpio(gpio_arr[i]);
			if (err < 0) fprintf(stderr, "Error in export_gpio()\n");
		}
	}

	// Configure as outputs and initialize high
	for (int i = 0; i < 8; i++) {
		err = set_direction(gpio_arr[i], "out");
		if (err < 0) {
			fprintf(stderr, "Error setting GPIO%s as output\n", gpio_arr[i]);
			continue;
		}
		err = set_gpio_high(gpio_arr[i]);
		if (err < 0) {
			fprintf(stderr, "Error initializing GPIO%s to high\n", gpio_arr[i]);
			continue;
		}
	}
}

// Function gets the first number from loadavg file
// returns -1 on error, 0 on success
float get_load_average(void)
{
	FILE *f;
	char *load_avg = malloc(60), *first_num, *err;
	float out = 0.0;

	// Open the load avg file and check for error
	f = fopen("/proc/loadavg", "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening file\n");
		free(load_avg);
		return -1;
	}

	// Only one line in the file, get it and check for error
	err = fgets(load_avg, 30, f);
	if (err == NULL) {
		fprintf(stderr, "Error getting contents\n");
		free(load_avg);
		return -1;
	}

	// Get the first number and convert to float
	first_num = strtok(load_avg, " ");
	out = strtof(first_num, NULL);

	fclose(f);
	free(load_avg);

	return out;
}

// Thermometer code for part A turn off LEDs based on load
void thermometer_code(float load, char *arr[])
{
	if (load < 4.0) set_gpio_low(arr[7]);
	if (load < 2.0) set_gpio_low(arr[6]);
	if (load < 1.0) set_gpio_low(arr[5]);
	if (load < 0.5) set_gpio_low(arr[4]);
	if (load < 0.25) set_gpio_low(arr[3]);
	if (load < 0.125) set_gpio_low(arr[2]);
	if (load < 0.0625) set_gpio_low(arr[1]);
	if (load < 0.03125) set_gpio_low(arr[0]);
}
