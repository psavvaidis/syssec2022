#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

void help();

int main(int argc, char *argv[]){
    mpz_t p, g, a, b, secret_a, secret_b, public_a, public_b;
    char* outputFile = NULL;

    // initialize integers
    mpz_init(p);
    mpz_init(a);
    mpz_init(b);
    mpz_init(g);
    mpz_init(secret_a);
    mpz_init(secret_b);
    mpz_init(public_a);
    mpz_init(public_b);


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
    if(outputFile == NULL){
        printf("Error: you haven't specified output file.\n Type \"-h\" for options\n");
        return -1;
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
    mpz_powm(public_a, g, a, p);
    mpz_powm(public_b, g, b, p);

    // computing secret
    mpz_powm(secret_a, public_b, a, p);
    mpz_powm(secret_b, public_a, b, p);

    //validating that the secret is shared.
    if(mpz_cmp(secret_a, secret_b)==0){
        printf("Secret was successfully shared\n");
        //Writing the file
        FILE* output = fopen(outputFile, "w");
        gmp_fprintf(output, "%Zd, %Zd, %Zd\n", public_a, public_b, secret_a);
        fclose(output);
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

