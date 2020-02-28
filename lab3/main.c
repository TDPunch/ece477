/* Author: Tyler Punch
 * File: main.c
 * Purpose: Contains main function for testing functions and error checking
 */

#include <stdio.h>
#include <unistd.h>
#include "gpio.h"
#include "partA.h"
#include "partB.h"

int main(int argc, char *argv[])
{
	float load_avg = 0.0, prev_load_avg = 0.0;
	char arr[16] = {'0', '\0', '1', '\0', '2', '\0', '3', '\0',
					'4', '\0', '5', '\0', '6', '\0', '7', '\0'};
	char *gpio_arr[8];

	// Generate array of string pointers for GPIO0-7
	for(int i = 0; i < 8; i++) {
		gpio_arr[i] = arr + 2*i;
	}

	// Enable GPIOs, set as outputs, set high
	setup_gpio();

	// Main loop, every 5 seconds check loadavg file
	// and update LEDs
	while(1) {
		sleep(5);
		
		if (prev_load_avg < load_avg) {
			ascending(gpio_arr);
		}
		else if (load_avg > prev_load_avg) {
			descending(gpio_arr);
		}
		else {
			thermometer_code(load_avg, gpio_arr);
		}
		
		load_avg = get_load_average();
		printf("load %f\n", load_avg);
		prev_load_avg = load_avg;
	}
}
