/* Author: Tyler Punch
 * File: partB.c
 * Purpose: this file contains my something cool
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gpio.h"
#include "partA.h"

// Blink LEDs at ascending rate
void ascending(char *arr[])
{
	int delay = 3000000;
	for(int i = 0; i < 8; i ++) {
		usleep(delay/(i + 1));
		set_gpio_low(arr[i]);
		usleep(delay/(i + 1));
		set_gpio_high(arr[i]);
	}
}

// Blink LEDs at descending rate
void descending(char *arr[])
{
	int delay = 3000000;
	for (int i = 8; i > 0; i--) {
		usleep(delay/i);
		set_gpio_low(arr[i]);
		usleep(delay/i);
		set_gpio_high(arr[i]);
	}
}
