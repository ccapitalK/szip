#include"analyse.h"
#include"misc.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

st_char analytics_table[256];
char print_table=1;
unsigned char head;
unsigned char sorted_table[256];
short table_size=0;

void init_analytics_table(void){
    for(unsigned short i = 0; i < 256; ++i){
        analytics_table[i].count=0;
        analytics_table[i].seen=0;
    }
}

void analyse(void){
    unsigned char buf;
    while(read(infile,&buf,1)==1){
        ++analytics_table[buf].count;
        ++file_size;
    }
    while(table_size<256){
        long long best=-1;
        unsigned char bchar;
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
        printf("Table size: %d (0x%03x)\n", table_size, table_size);
        for(int i = 0; i < table_size; ++i)
            printf("%0d: %03d [0x%02x] (count: %12lld)\n", i, (int)sorted_table[i], (int)sorted_table[i],analytics_table[sorted_table[i]].count);
    }
}

void read_table(void){
    unsigned char buf;
    if(read(infile,&buf,1)!=1){
        printf("Error reading translation table size\n");
        exit(-1);
    }
    table_size=buf;
    if(table_size==0)
        table_size=256;
    if(read(infile,&file_size,sizeof(file_size))!=sizeof(file_size)){
        printf("Error reading archive file size\n");
        exit(-1);
    }
    if(file_size==0){
        printf("Expanded empty file.\n");
        exit(0);
    }
    for(short i = 0; i < table_size; ++i){
        if(read(infile,&sorted_table[i],1)!=1){
            printf("Error reading translation table\n");
            exit(-1);
        }
    }
    if(print_table){
        printf("Table size: %d (0x%03x)\n", table_size, table_size);
        for(int i = 0; i < table_size; ++i)
            printf("%03d: %03d [0x%02x]\n", i, (int)sorted_table[i], (int)sorted_table[i]);
    }
}
