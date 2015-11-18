#pragma once
#include<sys/types.h>

extern int infile, outfile;
extern off_t file_size;
extern short table_size;

void reg_pair(unsigned char, unsigned char);
int create_translation_table();

extern unsigned char _otn[256];
extern unsigned char _nto[256];


void compress();
void decompress();
