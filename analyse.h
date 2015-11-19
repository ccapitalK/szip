#pragma once

typedef struct{
    long long count;
    char seen;
} st_char;

extern st_char analytics_table[256];
void analyse(void);
void init_analytics_table(void);
void read_table(void);
extern unsigned char sorted_table[256];
