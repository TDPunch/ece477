/* Author: Tyler Punch
 * File: main.c
 * Purpose: Contains main function for testing functions and error checking
 */

#include <stdio.h>
#include <unistd.h>
#include "gpio.h"
#include "partA.h"

int main(int argc, char *argv[])
{
	int check = 0, err = 0;
	float load_avg;

	char arr[16] = {'0', '\0', '1', '\0', '2', '\0', '3', '\0',
					'4', '\0', '5', '\0', '6', '\0', '7', '\0'};
	char *gpio_arr[8];

	for(int i = 0; i < 8; i++) {
		gpio_arr[i] = arr + 2*i;
	}

	for(int i = 0; i < 8; i++) {
		check = check_export(gpio_arr[i]);
		if (check < 0) {
			err = export_gpio(gpio_arr[i]);
		}
	}

	for (int i = 0; i < 8; i++) {
		err = set_direction(gpio_arr[i], "out");
		if (err < 0) {
			fprintf(stderr, "Error setting GPIO%s as output\n", gpio_arr[i]);
			continue;
		}
		err = set_gpio_high(gpio_arr[i]);
		if (err < 0) {
			fprintf(stderr, "Error initializing GPIO%s to low\n", gpio_arr[i]);
			continue;
		}
	}

	
	while(1) {
		sleep(2);
		load_avg = get_load_average();
		printf("load %f\n", load_avg);
		thermometer_code(load_avg, gpio_arr);
	}
}
