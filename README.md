# Exercise 1
by Panagiotis Savvaidis: 2013030180

*gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0*

## Introduction
Goal of this exercise was the familiarization with the **Diffie-Hellman Key Exchange** and **RSA Encryption** algorithms using the **GNU Multiple Precision** Arithmetic Library (GMP). 

## Installation and deployment

* Unzip the file and 
* type `make` in your command line

To get help for Diffie Hellman, run  
``` 
./dh_assign_1 -h 
``` 
To get help for the RSA, run
```
./rsa_assign_1 -h 
``` 

## Diffie-Hellman Key Exchange
### Running the commands

In order to run the agorithm you run the command
```
./dh_assign_1 -o <outputfile> -p <num> -g<num> -a <num> -b <num>
```
Also, `a` and `b` must be **smaller** than `p`.

All tasks are implemented.

## RSA Encryption
### Running the commands

In order to generate the public and private keys, you first run the command
```
./rsa_assign_1 -g
```
You have to type 2 prime numbers when asked from the command line.

After that, 2 files are created, a *public-key.txt* and a *private-key.txt*

Then, to encrypt/decrypt an input file, you type
```
./rsa_assign_1 -i <inputfile> -o <outputfile> -k <keyfile> [-e/-d]
```
`-e` is for encryption, `-d` is for decryption

### Not implemented

The parts that are not implemented are the usage of `*.key`files, due to inability to properly create the *encoded* file.

Also, the checks are very minimal.