/* Author: Tyler Punch
 * File: main.c
 * Purpose: Contains main function for testing functions and error checking
 */

#include <stdio.h>
#include "gpio.h"

int main(int argc, char *argv[])
{
	int err = 0;

	err = export_gpio("17");
	if (err < 0) {
		fprintf(stderr, "Error in export_gpio()\n");
		return -1;
	}

	err = set_direction("17", "out");
	if (err < 0) {
		fprintf(stderr, "Error in set_direction()\n");
		return -1;
	}

	err = set_gpio_low("17");
	if (err < 0) {
		fprintf(stderr, "Error in set_gpio_low()\n");
		return -1;
	}
}
