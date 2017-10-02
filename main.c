//
//  main.c
//  Lab2
//
//  Created by Dillon Coffman on 9/17/17.
//  Copyright © 2017 Dillon Coffman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char *read_file(int len, char *filename);
char * make_rand_key(int length, char *key);
void write_file(int len, char *filename, char *output);
void encryptF(char *clear_file, char *key_file, char *cipher_file);
void decryptF(char *key_file, char *cipher_file, char *message_file);


int main(int argc, const char * argv[]) {
    // int for user's choice
    int choice = 0;
    // Loop until choice == 4
    while(choice != 4){
        printf("Menu\n");
        printf("Encrypt a file: 1\n");
        printf("Decrypt a file: 2\n");
        printf("Exit: 3\n");
        // Prompts user to select a choice from above list
        printf("Enter a choice: ");
        //gets the choice from user
        scanf("%d", &choice);
        switch (choice){
            case 1: // choice 1
                printf("You chose to encrypt.\n");
                encryptF("/Users/dilloncoffman/Desktop/tmp/test.txt", "/Users/dilloncoffman/Desktop/tmp/key.txt",
                         "/Users/dilloncoffman/Desktop/tmp/cipher.txt");
                printf("Performing encryption...\n\n");
                break;
            case 2: // choice 2
                decryptF("/Users/dilloncoffman/Desktop/tmp/key.txt", "/Users/dilloncoffman/Desktop/tmp/cipher.txt",
                         "/Users/dilloncoffman/Desktop/tmp/message.txt");
                printf("You chose to decrypt.\n");
                printf("Performing decryption...\n\n");
                break;
            case 3: // choice 3
                printf("Exiting...\n\n");
                exit(51);
                break;
            default: // default prompts user to enter a valid choice
                printf("Please enter a valid choice.\n\n");
                break;
        }
    }
    return 0;
}

char *read_file(int len, char *filename){
    FILE *ptrFile = fopen(filename, "r"); //open file for reading
    if(!ptrFile){ //if file does not exist
        fputs("Error: File not found.\n", stderr);
        exit(1);
    }
    
    if(len == 0){ //if length is 0, count length of file
        while(getc(ptrFile) != EOF){ //go through file until EOF read
            len++; //increment the size of file for each char read
        }
        rewind(ptrFile); //rewind to beginning of file
    }
    
    char *string = (char*) malloc(len+1); //allocate memory for string input, plus one for null
    int j = 0;
    for(j = 0; j < len; j++){
        string[j] = getc(ptrFile);
        
    }
    string[j] = '\0'; //puts null at end of string
    
    if(string == NULL){ //if there is no string to read
        fputs("No stringg to read.\n", stderr); //show error
        return NULL; //return nothing
    }
    
    printf("%s\n", string); //prints the string that was read in
    
    fclose(ptrFile); //closes the file
    free(string); //frees the memory
    return string; //returns the string read from file
}

void write_file(int len, char *filename, char *output){
    FILE *ptrFile = fopen(filename, "w"); //open file for writing
    if(ptrFile == NULL){
        printf("Error: File not opened.\n");
        exit(3);
    }
    
    int j = 0;
    if(len == 0){ //if length is 0
        while(output[j] != '\0'){
              putc(output[j++], ptrFile);
        }
    } else {
        for(j=0; j < len; j++){
            putc(output[j], ptrFile);
        }
    }
    
    fclose(ptrFile);
    return;
}



char * make_rand_key(int length, char *key){

    key = (char*) malloc(length+1); //allocate memory for key, based off length of string
    time_t t = 0;
    
    
    int i = 0;
    for( i = 0; i < length; i++){
        srand((char)time(&t)); //seed the random generator
        key[i] = (char)rand() % 255; //input a random char into key
        if(key[i] == EOF){ //if EOF, make the value -2
            key[i] = EOF - 1;
        }
        if(key[i] == 0){ //if null, make it 1
            key[i] = 1;
        }
    }
    key[i] = '\0'; //add null at end
    
    return key;
}

void encryptF(char *clear_file, char *key_file, char *cipher_file){
    int length = 0;
    FILE *ptrk = fopen(key_file, "w");
    FILE *ptrc = fopen(clear_file, "r");
    
    
    char *input = read_file(length, clear_file);
    while(input[length]!='\0'){
        length++;
        printf("%i\n", length); //just to check have proper length
    }
    char * key = make_rand_key(length, input); //assign random key value to key
    char *cipher = (char*) malloc(length+1); //allocate memory for cipher
    
    write_file(length, key_file, key); //write the key to file
    
    for(int i = 0; i < length; i++){ //go through clear file and key file, exclusive or'ing each byte to be put into cipher
        cipher[i] = getc(ptrk) ^ getc(ptrc);
    }
    write_file(length, cipher_file, cipher); //write the cipher to file
    fclose(ptrk); //close both files
    fclose(ptrc);
    free(cipher); //free cipher from memory
}

void decryptF(char *key_file, char *cipher_file, char *message_file){
    int length = 0;
    FILE *ptrk = fopen(key_file, "r"); //open all files necessary for decrypting
    FILE *ptrc = fopen(cipher_file, "r");
    FILE *ptrm = fopen(message_file, "w");
    
    char *key = read_file(length, key_file); //read key file
    char *cipher = read_file(length, cipher_file); //read cipher file
    char *message = (char*) malloc(length+1); //allocate memory for the decrypted message

    
    while(key[length]!='\0'){ //get length of key file
        length++;
        printf("%i\n", length); //print to length to check if correct
    }
    
    while(cipher[length] != '\0'){ //print length to check if correct
        length++;
        printf("%i\n", length);
    }
    
    for(int i = 0; i < length; i++){ //go through key file and cipher file, exclusive or'ing each byte to be stored in message
        message[i] = getc(ptrk) ^ getc(ptrc);
    }
    
    write_file(length, message_file, message); //write the decrypted message to file
    fclose(ptrm); //close all files
    fclose(ptrk);
    fclose(ptrc);
    free(message); //free message
}
