#ifndef PARTA_H
#define PARTA_H

void setup_gpio(void);
float get_load_average(void);
void thermometer_code(float load, char *arr[]);

#endif
