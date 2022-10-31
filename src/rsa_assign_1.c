#include <stdio.h>
#include <gmp.h>

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

void encrypt();
void decrypt();
void generate();

int main(int argc, char *argv[]){
    FILE *input_f = NULL, *output_f = NULL, *key_f = NULL;
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

