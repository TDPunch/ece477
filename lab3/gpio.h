#ifndef GPIO_H
#define GPIO_H

int export_gpio(char *pin);
int set_direction(char *pin, char *IO);
int set_gpio_high(char *pin);
int set_gpio_low(char *pin);

#endif
