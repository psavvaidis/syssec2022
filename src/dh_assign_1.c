#include <stdio.h>
#include <gmp.h>

void help();

int main(int argc, char *argv[]){

    mpz_t p, g, a, b;
    help();

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
