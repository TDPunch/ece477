#ifndef MOON_PHASE_H
#define MOON_PHASE_H

// MAX_LINE_SIZE is 80 which is long enough to get a string 
// containing a phase of the moon (engineering design choice).
#define MAX_LINE_SIZE 80

FILE *get_json(void);
int find_phase(FILE *f);
void print_phase(char *str);

#endif
