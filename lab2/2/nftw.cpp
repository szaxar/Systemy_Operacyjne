#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include<stdlib.h>
#include <cstring>

#include  <sys/types.h>
#include  <sys/stat.h>
#include <unistd.h>


#include <ftw.h>

using namespace std;

int x=0;
int info(const char * nazwa_sciezki , const struct stat *fileStat, int tflag, struct FTW *ftwbuf){


if(fileStat->st_size>x){
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
return 0;
}


void search_nftw(int argc, char *path){
    x=argc;
    int flags = 0;
    flags |= FTW_DEPTH;
    flags |= FTW_PHYS;
    if (nftw(path, info, 20, flags)== -1) {
      perror("nftw");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main( int argc, char ** argv ) {
int x=atoi(argv[2]);
    if( argc > 1 )
      
search_nftw(x,argv[1]);

   return 0;
} 
