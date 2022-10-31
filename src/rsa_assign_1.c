#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <stdlib.h>

void help(){
    printf("Options:\n\
    -i\tpath\tPath to input file\n\
    -o\tpath\tPath to output file\n\
    -k\tpath\tPath to key file\n\
    -g\t\tPerform RSA key-pairgeneration\n\
    -d\t\tDecrypt input and store results to output\n\
    -e\t\tEncrypt input and store results to output\n\
    -h\t\tThis help message\n");
}

void encrypt(char*, char*, char*);
void decrypt(char*, char*, char*);
void generate();

int main(int argc, char *argv[]){
    char *input_f = NULL, *output_f = NULL, *key_f = NULL;
    int toEncrypt = 0;
    int toDecrypt = 0;

    for (int i = 1; i < argc; i++){
        // print help
        if(strcmp(argv[i],"-h") == 0){
            help();
            return 0;
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-i")==0){
            input_f = (char*)malloc(strlen(argv[++i]));
            strcpy(input_f, argv[i]);
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-o")==0){
            output_f = (char*)malloc(strlen(argv[++i]));
            strcpy(output_f, argv[i]);
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-k")==0){
            key_f = (char*)malloc(strlen(argv[++i]));
            strcpy(key_f, argv[i]);
        }else if(strcmp(argv[i],"-g")==0){
            generate();
            return 0;
        }
        else if(strcmp(argv[i],"-d")==0 && !toEncrypt){
            toDecrypt = 1;
        }
        else if(strcmp(argv[i],"-e")==0 && !toDecrypt){
            toEncrypt = 1;
        }
    }

    if(toEncrypt){
        encrypt();
    }else if (toDecrypt){
        decrypt();
    }

    return 0;
}

void generate(){
    mpz_t p,q, n, lambda_n, e, d;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(d);
    mpz_init(lambda_n);
    mpz_init_set_ui(e, 3);

    // Read User Input and checkif prime
    printf("Enter prime number p: ");
    gmp_scanf("%Zd", p);
    while(mpz_probab_prime_p(p, 24) == 0){
        printf("The number you have entered is not a prime number.\nTry again: ");
        gmp_scanf("%Zd", p);
    }
    printf("Enter prime number q: ");
    gmp_scanf("%Zd", q);
    while(mpz_probab_prime_p(q, 24) == 0){
        printf("The number you have entered is not a prime number.\nTry again: ");
        gmp_scanf("%Zd", q);
    }

    // Calculate n = p*q
    mpz_mul(n, q, p);   

    // Calculate lambda_n = (p-1)*(q-1)
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
    mpz_mul(lambda_n,p,q);

    // Calculate d
    mpz_invert(d, e, lambda_n);

    FILE *public_f = NULL;
    FILE *private_f = NULL;

    public_f = fopen("public_key.txt", "w+");
    gmp_fprintf(public_f, "%Zd\n", n);
    gmp_fprintf(public_f, "%Zd\n", d);
    fclose(public_f);
    
    private_f = fopen("private_key.txt", "w+");
    gmp_fprintf(private_f, "%Zd\n", n);
    gmp_fprintf(private_f, "%Zd\n", e);
    fclose(private_f);

}

void encrypt(char* inputFileName, char* outputFileName, char* keyFileName){

}
void decrypt(char* inputFileName, char* outputFileName, char* keyFileName){}

