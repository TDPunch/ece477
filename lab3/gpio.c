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
	int fd = 0, err = 0;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error enabling GPIO\n");
		return -1;
	}

	sleep(2);
	
	err = write(fd, pin, 2);
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

	printf("%s\n", filename);
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

	printf("%s\n", filename);
	fd = open(filename, O_WRONLY);
	free(filename);

	if (fd < 0) return -1;
	else {
		close(fd);
		return 0;
	}
}

void export_all(void)
{
	int check = 0, err;
	char *gpio_0 = "0", *gpio_1 = "1", *gpio_2 = "2", *gpio_3 = "3";
	char *gpio_4 = "4", *gpio_5 = "5", *gpio_6 = "6", *gpio_7 = "7";

	check = check_export(gpio_0);
	if (check < 0) {
		err = export_gpio(gpio_0);
	}

	check = check_export(gpio_1);
	if (check < 0) {
		err = export_gpio(gpio_1);
	}

	check = check_export(gpio_2);
	if (check < 0) {
		err = export_gpio(gpio_2);
	}

	check = check_export(gpio_3);
	if (check < 0) {
		err = export_gpio(gpio_3);
	}

	check = check_export(gpio_4);
	if (check < 0) {
		err = export_gpio(gpio_4);
	}

	check = check_export(gpio_5);
	if (check < 0) {
		err = export_gpio(gpio_5);
	}

	check = check_export(gpio_6);
	if (check < 0) {
		err = export_gpio(gpio_6);
	}

	check = check_export(gpio_7);
	if (check < 0) {
		err = export_gpio(gpio_7);
	}
}

void direction_all(void)
{
	char *gpio_0 = "0", *gpio_1 = "1", *gpio_2 = "2", *gpio_3 = "3";
	char *gpio_4 = "4", *gpio_5 = "5", *gpio_6 = "6", *gpio_7 = "7";

	
}
