/* Author: Tyler Punch
 * File: gpio.c
 * Purpose: This file contains function relating to ECE 477 Lab 3
 */

#include <unistd>
#include <>
int export_gpio(char *pin)
{
	int fd = 0, err = 0;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		fprintf(stderr, "Error enabling GPIO\n");
		return -1;
	}

	err = write(fd, pin, strlen(pin));
	if (err < 0) {
		fprintf(stderr, "Error writing to file\n");
		return -1;
	}

	sleep(1);
	close(fd);

	return 0;
}

int set_direction()
{

}
