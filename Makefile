.DEFAULT_GOAL := compile

compile:
	gcc -o dh_assign_1 src/dh_assign_1.c -lgmp
	gcc -o rsa_assign_1 src/rsa_assign_1.c -lgmp

