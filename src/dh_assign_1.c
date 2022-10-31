#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

void help();

int main(int argc, char *argv[]){
    mpz_t p, g, a, b;
    char* outputFile = NULL;

    for (int i = 1; i < argc; i++){
        if(strcmp(argv[i],"-h") == 0){
            help();
            return 0;
        }else if(strcmp(argv[i],"-o")==0){
            outputFile = (char*)malloc(strlen(argv[++i]));
            strcpy(outputFile, argv[i]);
        }
    }

    
    printf("%s",outputFile);

    return 0;
}

void help(){
    printf("Options:\n\
    -o\tpath\tPath to output file\n\
    -p\tnumber\tPrime Number\n\
    -g\tnumber\tPrimitive Root for previous prime number\n\
    -a\tnumber\tPrivate key A\n\
    -b\tnumber\tPrivate key B\n\
    -h\t\tThis help message\n");
}
