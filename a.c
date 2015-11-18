#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include"misc.h"
#include"analyse.h"
#define COMP 0
#define EXP 1

char mode;
int infile, outfile;
off_t file_size;
const unsigned char pivot=5;

//compress human readable, decompress human writeable
void decompress(){

}

unsigned short wr_b=0;
unsigned char  wr_c=0;
void flush_mbuf(void){
    //printf("%04x\n",wr_b);
    unsigned char buf=wr_b>>8;
    wr_b<<=8;
    write(outfile,&buf,1);
}

void m_write_1(unsigned char ch){
    const unsigned char mask=((1<<pivot)-1);
    if(ch<mask){
        wr_b|=ch<<(15-pivot-wr_c);
        wr_c+=pivot;
        if(wr_c>=8){
            flush_mbuf();
            wr_c-=8;
        }
    }else{
        wr_b|=mask<<(16-pivot-wr_c);
        wr_c+=pivot;
        if(wr_c>=8){
            flush_mbuf();
            wr_c-=8;
        }
        wr_b|=ch<<(8-wr_c);
        wr_c+=8;
        if(wr_c>=8){
            flush_mbuf();
            wr_c-=8;
        }
    }
}

void compress(){
    write(outfile,&table_size,1);
    write(outfile,&file_size,sizeof(file_size));
    for(short i=0; i<table_size; ++i)
        write(outfile,&sorted_table[i],1);
    lseek(infile,0,SEEK_SET);
    unsigned char buf;
    while(read(infile,&buf,1)==1){
        buf=_otn[buf];
        m_write_1(buf);
    }
    if(wr_c){
        flush_mbuf();
        wr_c=0;
    }
}

int main(int argc, char *argv[]){
    if(argc!=4){
        fprintf(stderr,"usage: [-c/-d] inputfile outputfile\n");
    }
    if(!strcmp(argv[1],"-c")){
        printf("Compressing\n");
        mode = COMP;
    }else if(!strcmp(argv[1],"-d")){
        printf("Decompressing\n");
        mode = EXP;
    }
    infile=open(argv[2],O_RDONLY);
    if(infile==-1){
        fprintf(stderr, "Error opening input file: \"%s\" (errno is %d)\n",argv[2],errno);
        return errno;
    }
    outfile=open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if(outfile==-1){
        fprintf(stderr,"Error opening output file: \"%s\" (errno is %d)\n",argv[3],errno);
        close(infile);
        return errno;
    }
    if(mode==COMP){
        init_analytics_table();
        analyse();
        create_translation_table();
        compress();
    }else if(mode==EXP){
        read_table();
        decompress();
    }
    close(infile);
    close(outfile);
    return 0;
}
