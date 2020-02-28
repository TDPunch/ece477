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

float get_load_average(void)
{
	FILE *f;
	char *load_avg = malloc(512), *first_num, *err;
	float out = 0.0;

	f = fopen("/proc/loadavg", "r");
	if (f == NULL) {
		fprintf(stderr, "Error opening file\n");
		return -1;
	}

	err = fgets(load_avg, 30, f);
	if (err == NULL) {
		fprintf(stderr, "Error getting contents\n");
		return -1;
	}

	first_num = strtok(load_avg, " ");
	out = strtof(first_num, NULL);

	fclose(f);
	free(load_avg);

	return out;
}

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
