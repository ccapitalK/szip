#include"misc.h"
#include<stdio.h>
#include"analyse.h"

unsigned char _otn[256];
unsigned char _nto[256];

int create_translation_table(void){
    for(short n=0; n<table_size; ++n)
        reg_pair(sorted_table[n],n);
    return 0;
}

//_ot = original alphabet, _nt = new alphabet

void reg_pair(unsigned char _ot, unsigned char _nt){
    _otn[_ot]=_nt;
    _nto[_nt]=_ot;
}

