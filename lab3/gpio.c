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

int export_gpio(char * pin)
{
	int fd = 0, err = 0, count = 0;
	char buf[2];

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error enabling GPIO\n");
		return -1;
	}

	sleep(2);

	count = sprintf(buf, "%s\n", pin);

	err = write(fd, buf, count);
	if (err < 0) {
		fprintf(stderr, "Error writing to exp\n");
		return -1;
	}

	close(fd);

	return 0;
}

int set_direction(char * pin, char *IO)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *direction = "/direction";
	char *filename;
	
	// Allocate memory for the full file name
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(direction) + 1);

	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, direction);

	fd = open(filename, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening 'direction' file\n");
		return -1;
	}

	err = write(fd, IO, strlen(IO));
	if (err < 0) {
		fprintf(stderr, "Error writing to dir\n");
		return -1;
	}

	close(fd);
	free(filename);

	return 0;
}

int set_gpio_high(char * pin)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *value = "/value";
	char *filename;
	
	// Allocate memory for the full file name
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(value) + 1);

	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, value);

	fd = open(filename, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening 'value' file\n");
		return -1;
	}

	err = write(fd, "1", 1);
	if (err < 0) {
		fprintf(stderr, "Error writing to file\n");
		return -1;
	}

	close(fd);
	free(filename);

	return 0;
}

int set_gpio_low(char * pin)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *value = "/value";
	char *filename;
	
	// Allocate memory for the full file name
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(value) + 1);

	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, value);

	fd = open(filename, O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error opening 'value' file\n");
		return -1;
	}

	err = write(fd, "0", 1);
	if (err < 0) {
		fprintf(stderr, "Error writing to file\n");
		return -1;
	}

	close(fd);
	free(filename);

	return 0;
}

int check_export(char * pin)
{
	int fd = 0, err = 0;
	char *gpio_dir = "/sys/class/gpio/gpio";
	char *value = "/value";
	char *filename;
	
	// Allocate memory for the full file name
	filename = malloc(strlen(gpio_dir) + strlen(pin) + strlen(value) + 1);

	strcat(filename, gpio_dir);
	strcat(filename, pin);
	strcat(filename, value);

	fd = open(filename, O_WRONLY);
	free(filename);

	if (fd < 0) return -1;
	else {
		close(fd);
		return 0;
	}
}
