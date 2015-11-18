#include"analyse.h"
#include"misc.h"
#include<unistd.h>
#include<stdio.h>

st_char analytics_table[256];
char print_table=1;
unsigned char head;
char sorted_table[256];
short table_size=0;

void init_analytics_table(){
    for(unsigned short i = 0; i < 256; ++i){
        analytics_table[i].count=0;
        analytics_table[i].seen=0;
    }
}

void analyse(){
    unsigned char buf;
    while(read(infile,&buf,1)==1){
        ++analytics_table[buf].count;
        ++file_size;
    }
    while(table_size<256){
        long long best=-1;
        char bchar;
        for(int i = 0; i < 256; ++i){
            if((!analytics_table[i].seen)&&analytics_table[i].count>=best){
                best=analytics_table[i].count;
                bchar=i;
            }
        }
        if(best==0){
            break;
        }else{
            analytics_table[bchar].seen=1;
            sorted_table[table_size++]=bchar;
        }
    }
    if(print_table){
        printf("Table size: %d (0x%x)\n", table_size, table_size);
        for(int i = 0; i < table_size; ++i)
            printf("%3d: %3d[0x%2x] (count: %12ld)\n", i, (int)sorted_table[i], (int)sorted_table[i],analytics_table[sorted_table[i]].count);
    }
}

void read_table(){}
