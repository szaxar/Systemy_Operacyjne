#include<iostream>
#include<string>
#include <string.h> 
#include<stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include <unistd.h>
#include <time.h>

static char* Random=(char*)"/dev/urandom";

enum Function{shuffle,sort,generate };

enum Arguments{file,version,record_size,file_size,function,trash};

struct Option{
char* fileName;
char version;
int recordSize;
int records;
enum Function function;
};

enum Arguments what_is_it(char *x){
    if (strcmp( x, "-file") == 0) return file;
    else
    if(strcmp( x, "-version") == 0) return version;
    else
    if(strcmp(x, "-fsize") == 0) return file_size;
    else
    if(strcmp(x, "-rsize")==0) return record_size;
    else
    if(strcmp(x, "-fun")==0) return function;
    else return trash;
}

enum Function descript_function(char * function){
    if (strcmp(function, "generate") == 0 ) return generate;
    if (strcmp(function, "shuffle") == 0 ) return shuffle;
    if (strcmp(function, "sort") == 0 ) return sort;
    printf("\nUnknown function!\n");



}


Option*  parser(int argc, char *argv[]){
	Option *option=(Option*)malloc(sizeof(option ));
	Arguments arg;
	for(int i=0;i<argc;i++){
	arg=what_is_it(argv[i]);

switch(arg){
            case file:
                option->fileName=argv[i+1];
                break;
            case version:
                option->version=argv[i+1][0];
                break;
            case file_size:
                option->records=atoi(argv[i+1]);
                break;
            case record_size:
                option->recordSize = atoi(argv[i+1]);
                break;
            case function:
                option->function=descript_function(argv[i+1]);
                break;

            default:
                break;

	}

				}

	return option;
}


int check_if_correct(Option* option){
    if(option->records<1) {
        printf("\nAmount of records can not be less than 1!\n");
        return -1;
    }
    if(option->recordSize<1){
        printf("\nRecord size can not be less than 1!\n");
        return -2;
    }
    if(!option->version == 'l' && !option->version == 's'){
        printf("\nVersion of program are:\ns-for system functions\nl - for library functions");
        return -2;
    }

    return 0;


}

void swap_l(FILE * file, int recrod1, int record2, int recordSize){
    char tmp[recordSize+sizeof(char)];
    char res[recordSize+sizeof(char)];

    fseek(file, recrod1*(recordSize+1), 0); // znajdz 1 rekod
    fread(res, sizeof(char),recordSize+1, file);  //zapisz do res
    strcpy(tmp,res);

    fseek(file, record2*(recordSize+1), 0); //znajdz 2
    fread(res, sizeof(char),  recordSize+1, file);
    fseek(file, recrod1*(recordSize+1), 0);

    fputs(res, file);
    fseek(file, record2*(recordSize+1), 0);//zapisz tmp ->re
    fputs(tmp,  file);
}

void shuffle_l(char * filename, int recordSize, int records){
    FILE *file =fopen(filename, "r+"); // read with update;

    int i, j;
    for( i = records-1; i>0; i--){
        j=rand()%(i+1);
        swap_l(file, i, j, recordSize);
    }
    fclose(file);
}



void swap_s(int file, int record1, int record2, int recordSize){

    char tmp[recordSize+sizeof(char)];
    char res[recordSize+sizeof(char)];

    lseek(file, record1*(recordSize+1), SEEK_SET);
    read(file, res, (size_t)(recordSize +1)); // znajdz 1 rekod
    strcpy(tmp,res);
    lseek(file, record2*(recordSize+1), SEEK_SET); //znajdz 2
    read(file, res,  recordSize+1);
    lseek(file, record1*(recordSize+1), SEEK_SET);
    write(file, res, (size_t)(recordSize+1));
    lseek(file, record2*(recordSize+1), SEEK_SET);//zapisz tmp ->re
    write(file,  tmp, (size_t)(recordSize+1));

}

void shuffle_s(char * filename, int recordSize, int records){
    int file= open(filename, O_RDWR);

    int i, j;
    for( i = records-1; i>0; i--){
        j=rand()%(i+1);
        swap_s(file, i, j, recordSize);
    }
}

void _generate(char* outputFileName, int record_size, int records) {

    int output = open(outputFileName, O_CREAT|O_APPEND|O_WRONLY,  S_IRUSR |S_IWUSR|  S_IRGRP | S_IROTH | S_IWOTH |S_IXOTH );
    int input = open(Random, O_RDONLY);
    char byte;

    for (int record = 0; record < records; record++) {
        for (int b = 0; b < record_size; b++) {
            read(input, &byte, sizeof(byte));
            write(output, &byte, sizeof(byte));

        }
        byte='\n';
        write(output, &byte, sizeof(byte));

    }
    close(output);
    close(input);

}




void shufflee(char * filename, int recordSize, int records, char version){
    switch(version){
        case 's':
            shuffle_s(filename, recordSize, records);
            break;
        case 'l':
            shuffle_l(filename, recordSize, records);
            break;
        default:
            printf("\nerrUnknown option!\n");
            break;

    }



}

int compare_l( FILE * file, int index1, int index2, int recordSize){
    char record1[recordSize+sizeof(char)];
    char record2[recordSize+sizeof(char)];

    fseek(file, index1*(recordSize+1), 0); // znajdz 1 rekod
    fread(record1, sizeof(char),recordSize+1, file);
    fseek(file, index2*(recordSize+1), 0); // znajdz 1 rekod
    fread(record2, sizeof(char),recordSize+1, file);

    if(record1[0]<record2[0]) return -1;
    if(record1[0]==record2[0]) return 0;
    return 1;



}

int compare_s( int file, int index1, int index2, int recordSize){
    char record1[recordSize+sizeof(char)];
    char record2[recordSize+sizeof(char)];
    lseek(file, index1*(recordSize+1), SEEK_SET);
    read(file, record1, recordSize+1);
    lseek(file, index2*(recordSize+1), SEEK_SET);
    read(file, record2, recordSize+1);

    if(record1[0]<record2[0]) return -1;
    if(record1[0]==record2[0]) return 0;
    return 1;



}

void bubble_sort_l(FILE * file, int records, int recordSize){
    for(int i=0; i<records; i++)
        for(int j=0; j< records-i-1; j++){
            if(compare_l(file, j, j+1, recordSize) >0)
                swap_l(file, j, j+1, recordSize);
        }

}

void bubble_sort_s(int file, int records, int recordSize){
    for(int i=0; i<records; i++)
        for(int j=0; j< records-i-1; j++){
            if(compare_s(file, j, j+1, recordSize) >0)
                swap_s(file, j, j+1, recordSize);
        }

}


void bubble(char * filename, int records, int recordSize, char option){
    FILE * file=fopen(filename, "r+");
    int file1=open(filename, O_RDWR);
    switch (option){

        case 'l':

            bubble_sort_l(file, records, recordSize);
            break;
        case 's':
            bubble_sort_s(file1,records,recordSize);
            break;

    }
    fclose(file);
    close(file1);
}




int main(int argc, char *argv[]){
 
Option* option=parser(argc,argv);

if(check_if_correct(option)==0)
        switch(option->function){
            case generate:
                _generate(option->fileName,option->recordSize,option->records);
                break;
            case shuffle:
                shufflee(option->fileName,option->recordSize, option->records,option->version);
                break;
            case sort:
bubble(option->fileName, option->records, option->recordSize, option->version);
  break;
            default:
                printf("\nUnknown function\nUse -fun {generate, shuffle, sort}\n");
}
 
return 0;
}
