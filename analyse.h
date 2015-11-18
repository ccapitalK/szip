#pragma once

typedef struct{
    long long count;
    char seen;
} st_char;

extern st_char analytics_table[256];
void analyse();
void init_analytics_table();
void read_table();
extern char sorted_table[256];
