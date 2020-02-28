#ifndef GPIO_H
#define GPIO_H

int export_gpio(char *pin);
int check_export(char *pin);
void export_all(void);

int set_direction(char *pin, char *IO);
int set_gpio_high(char *pin);
int set_gpio_low(char *pin);

#endif
