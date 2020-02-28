/* Author: Tyler Punch
 * File: gpio.c
 * Purpose: This file contains function relating to ECE 477 Lab 3
 */

/* open() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h> /* close() */
#include <string.h>
#include <stdio.h>

#include "gpio.h"

// Function enables GPIO based on pin number,
// return -1 on error, 0 on success
int export_gpio(char *pin)
{
	int fd = 0, err = 0, count = 0;
	char buf[2];

	// Open export file for enabling GPIO
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error enabling GPIO\n");
		return -1;
	}

	// Write the pin to a buffer to avoid write errors
	count = sprintf(buf, "%s\n", pin);
	err = write(fd, buf, count);
	if (err < 0) {
		fprintf(stderr, "Error writing to exp\n");
		return -1;
	}

	// Close export file and wait for export process, can be long
	close(fd);
	sleep(1);

	return 0;
}

// Configure GPIO as input or output
int set_direction(char *pin, char *IO)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *direction = "/direction";
	char *filename;
	
	// Allocate memory for the full file name and build it
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(direction) + 1);
	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, direction);

	// Open direction file for GPIO
	fd = open(filename, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening 'direction' file\n");
		free(filename);
		return -1;
	}

	// Configure as in or out, based on input
	err = write(fd, IO, strlen(IO));
	if (err < 0) {
		fprintf(stderr, "Error writing to dir\n");
		free(filename);
		return -1;
	}

	close(fd);
	free(filename);

	return 0;
}

// Turn on LED, returns -1 on error, 0 on success
int set_gpio_high(char *pin)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *value = "/value";
	char *filename;
	
	// Allocate memory for the full file name and build it
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(value) + 1);
	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, value);

	// Open value file to change state
	fd = open(filename, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening 'value' file\n");
		free(filename);
		return -1;
	}

	// Set it high
	err = write(fd, "1", 1);
	if (err < 0) {
		fprintf(stderr, "Error writing to file\n");
		free(filename);
		return -1;
	}

	close(fd);
	free(filename);

	return 0;
}

// Shut of LED, returns -1 on error, 0 on success
int set_gpio_low(char *pin)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *value = "/value";
	char *filename;
	
	// Allocate memory for the full file name and build it
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(value) + 1);
	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, value);

	// Open value file to change state
	fd = open(filename, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening 'value' file\n");
		free(filename);
		return -1;
	}

	// Set is low
	err = write(fd, "0", 1);
	if (err < 0) {
		fprintf(stderr, "Error writing to file\n");
		free(filename);
		return -1;
	}

	close(fd);
	free(filename);

	return 0;
}

// This function checks if GPIO has been enabled so that 
// export_gpio() doesn't cause unnecessary delay
// returns -1 if GPIO has already been enabled, 0 if not
int check_export(char *pin)
{
	int fd = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *value = "/value";
	char *filename;
	
	// Allocate memory for the full file name and build it
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(value) + 1);
	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, value);

	// Try to open the file and make sure to free the memory
	fd = open(filename, O_WRONLY);
	free(filename);

	if (fd < 0) return -1;
	else {
		close(fd);
		return 0;
	}
}
