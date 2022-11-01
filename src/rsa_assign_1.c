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
    char *input = NULL, *output = NULL, *key = NULL;
    int toEncrypt = 0;
    int toDecrypt = 0;

    for (int i = 1; i < argc; i++){
        // print help
        if(strcmp(argv[i],"-h") == 0){
            help();
            return 0;
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-i")==0){
            input = (char*)malloc(strlen(argv[++i]));
            strcpy(input, argv[i]);
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-o")==0){
            output = (char*)malloc(strlen(argv[++i]));
            strcpy(output, argv[i]);
        }// get the output file name from arguments
        else if(strcmp(argv[i],"-k")==0){
            key = (char*)malloc(strlen(argv[++i]));
            strcpy(key, argv[i]);
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
        encrypt(input, output, key);
    }else if (toDecrypt){
        decrypt(input, output, key);
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

    FILE *public = NULL;
    FILE *private = NULL;

    public = fopen("public_key.txt", "w+");
    gmp_fprintf(public, "%Zd\n%Zd\n", n, d);
    fclose(public);
    
    private = fopen("private_key.txt", "w+");
    gmp_fprintf(private, "%Zd\n%Zd\n", n, e);
    fclose(private);

}

void encrypt(char* inputFileName, char* outputFileName, char* keyFileName){
    FILE *input, *output, *key;
    mpz_t n, e;
    mpz_init(n); mpz_init(e);
    // Get key components
    key = fopen(keyFileName, "r");
    gmp_fscanf(key,"%Zd\n%Zd\n", n, e);
    fclose(key);

    input = fopen(inputFileName, "r");
    output = fopen(outputFileName, "w+");
    while(1){
        char c = fgetc(input);
        if(c == EOF){ break;}

        char *padded_c = (char *)malloc(8);
        sprintf(padded_c, "%08d", c);
        mpz_t cipher;
        mpz_init(cipher);

        mpz_set_str(cipher,padded_c, 0);
        // gmp_printf("%08d\n", cipher);
        mpz_powm(cipher, cipher, e, n);
        gmp_fprintf(output,"%08Zd", cipher);
    }
    
    fclose(input);
    fclose(output);
}

void decrypt(char* inputFileName, char* outputFileName, char* keyFileName){
    
}

