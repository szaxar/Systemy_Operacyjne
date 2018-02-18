#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <cstring>

#include  <sys/types.h>
#include  <sys/stat.h>
#include <unistd.h>
#include <ctime>
using namespace std;


void info(const char * nazwa_sciezki , int x ){

struct stat *fileStat;
int result =stat(nazwa_sciezki,fileStat);
 
if(result==0 && fileStat->st_size>x){
    printf("Information for %s\n",nazwa_sciezki);
    printf("---------------------------\n");
    printf("File Size: \t\t%d bytes\n",fileStat->st_size);
    printf("Date :%d\n",fileStat->st_mtime);
 
    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat->st_mode)) ? "d" : "-");
    printf( (fileStat->st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat->st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat->st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat->st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat->st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat->st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat->st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat->st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat->st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
 
}

}



void listujPliki( char * nazwa_sciezki,int x ) {


	info(nazwa_sciezki,x);

    struct dirent * plik;
    DIR * sciezka;
   const char * nazwa=nazwa_sciezki;

    if(( sciezka = opendir( nazwa ) ) ) {
		
        while(( plik = readdir( sciezka ) ) ){
    if(plik->d_name[0]!='.')  {

string tmp=nazwa_sciezki;
tmp=tmp+'/';
tmp=tmp+plik->d_name;
char *y = new char[tmp.length() + 1]; 
strcpy(y, tmp.c_str());

listujPliki(y,x);

				}
    
}
        closedir( sciezka );
    }
   
       
 
}

int main( int argc, char ** argv ) {
int x=atoi(argv[2]);
    if( argc > 1 )
         listujPliki( argv[ 1 ] , x );
    


   return 0;
} 
