#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

void help();

int main(int argc, char *argv[]){
    mpz_t p, g, a, b, secret_a, secret_b, a_sends, b_sends;
    char* outputFile = NULL;

    // initialize integers
    mpz_init(p);
    mpz_init(a);
    mpz_init(b);
    mpz_init(g);
    mpz_init(secret_a);
    mpz_init(secret_b);
    mpz_init(a_sends);
    mpz_init(b_sends);


    for (int i = 1; i < argc; i++){
        // print help
        if(strcmp(argv[i],"-h") == 0){
            help();
            return 0;
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-o")==0){
            outputFile = (char*)malloc(strlen(argv[++i]));
            strcpy(outputFile, argv[i]);
        }// get p value from arguments
        else if(strcmp(argv[i],"-p")==0){
            mpz_set_str(p, argv[++i],0);
        }// get g value from arguments
        else if(strcmp(argv[i],"-g")==0){
            mpz_set_str(g, argv[++i],0);
        }// get a value from arguments
        else if(strcmp(argv[i],"-a")==0){
            mpz_set_str(a, argv[++i],0);
        }// get b value from arguments
        else if(strcmp(argv[i],"-b")==0){
            mpz_set_str(b, argv[++i],0);
        }
    }
    if(mpz_cmp(a, p)>0){
        printf("a must be smaller than p. try again.\n");
        return -1;
    }
    if(mpz_cmp(b, p)>0){
        printf("b must be smaller than p. try again.\n");
        return -1;
    }


    // computing nums to be sent
    mpz_powm(a_sends, g, a, p);
    mpz_powm(b_sends, g, b, p);

    // computing secret
    mpz_powm(secret_a, b_sends, a, p);
    mpz_powm(secret_b, a_sends, b, p);

    if(mpz_cmp(secret_a, secret_b)==0){
        printf("Secret was successfully shared\n");
        gmp_printf("%Zd, %Zd\n", secret_a, secret_b);
    }else{
        printf("Error sharing secret\n");
    }

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

