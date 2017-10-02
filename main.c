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
void make_rand_key(int length, char *key);
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
                printf("You chose to encrypt this message: ");
                encryptF("/Users/dilloncoffman/Desktop/tmp/test.txt", "/Users/dilloncoffman/Desktop/tmp/key2.txt",
                         "/Users/dilloncoffman/Desktop/tmp/cipher2.txt");
                printf("Successfully encrypted your message.\n\n");
                break;
            case 2: // choice 2
                printf("You chose to decrypt and your decrypted message is: ");
                decryptF("/Users/dilloncoffman/Desktop/tmp/key2.txt", "/Users/dilloncoffman/Desktop/tmp/cipher2.txt",
                         "/Users/dilloncoffman/Desktop/tmp/message2.txt");
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
    if(!ptrFile){ //if file does not exist, throw error
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
    for(j = 0; j < len; j++){ //read in chars from file to string
        string[j] = getc(ptrFile);
        
    }
    string[j] = '\0'; //puts null at end of string
    
    if(string == NULL){ //if there is no string to read
        fputs("No stringg to read.\n", stderr); //show error
        return NULL; //return nothing
    }

    fclose(ptrFile); //closes the file
    return string; //returns the string read from file
}

void write_file(int len, char *filename, char *output){
    FILE *ptrFile = fopen(filename, "w"); //open file for writing
    if(ptrFile == NULL){ //if no file, throw error, exit program
        printf("Error: File not opened.\n");
        exit(3);
    }
    
    int j = 0;
    if(len == 0){ //if length is 0
        while(output[j] != '\0'){ //read file until null
              putc(output[j++], ptrFile); //writing each char to ptrFile
        }
    } else { //otherwise there is already a known length, just write each char to ptrFile
        for(j=0; j < len; j++){
            putc(output[j], ptrFile);
        }
    }
    
    fclose(ptrFile); //close file
    return;
}



void make_rand_key(int length, char *key){
    
    srand((char)time(NULL)); //seed the random generator
    
    int i = 0;
    for(i = 0; i < length; i++){
        key[i] = (char)rand() % 256; //input a random char into key
        if(key[i] == EOF){ //if EOF, make the value -2
            key[i] = EOF - 1;
        }
        if(key[i] == 0){ //if null, make it 1
            key[i] = 1;
        }
    }
    key[i] = '\0'; //add null at end
    
    return; //
}

void encryptF(char *clear_file, char *key_file, char *cipher_file){
    int length = 0; //declare and initialize length var to be used
    FILE *ptrk = fopen(key_file, "w"); //open files to do work on/with
    FILE *ptrc = fopen(clear_file, "r");
    
    
    char *input = read_file(length, clear_file); //read in contents from clear file, assign them to input
    printf("%s\n", input); //print input read in, to be used in console
    length = (int)strlen(input); //get length of the clear text to be used
    char key[length+1]; //initialize char array key with appropriate length needed
    char cipher[length+1]; //initialize char array cipher wiht appropriate length needed
    
    make_rand_key(length, key);
    
    write_file(length, key_file, key); //write the key to file
    
    for(int i = 0; i < length; i++){ //go through clear file and key file, exclusive or'ing each byte to be put into cipher
        cipher[i] = input[i] ^ key[i];
    }
    printf("\n");
    cipher[length] = '\0';
    
    write_file(length, cipher_file, cipher); //write the cipher to file
    fclose(ptrk); //close both files
    fclose(ptrc);
}

void decryptF(char *key_file, char *cipher_file, char *message_file){
    int length = 0; //declare and initialize length var to be used
    FILE *ptrk = fopen(key_file, "r"); //open all files necessary for decrypting
    FILE *ptrc = fopen(cipher_file, "r");
    FILE *ptrm = fopen(message_file, "w");
    
    char *key = read_file(length, key_file); //read key file
    length = (int) strlen(key); //get length of key to be used
    char *cipher = read_file(length, cipher_file); //read cipher file
    char message[length+1]; //clear out size for char array message
    
    for(int i = 0; i < length; i++){ //go through key file and cipher file, XOR'ing each byte to be stored in message
        message[i] = key[i] ^ cipher[i];
    }
    printf("%s\n\n", message); //print message result from XOR'ing, to be used in console
    
    write_file(length, message_file, message); //write the decrypted message to file
    fclose(ptrm); //close all files
    fclose(ptrk);
    fclose(ptrc);
}
