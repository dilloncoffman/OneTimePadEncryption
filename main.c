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
void write_file(int len, char *filename, char *output);

int main(int argc, const char * argv[]) {
    
    
    //need srand, using rand function
    //int arr[5];
    //before you call rand, must seed random generator
//    srand(time(NULL)); //seeds data so it's not the same as before, will need this for generating random key
//    arr[0] = rand() % 255;
//    arr[1] = rand() % 255;
//    arr[2] = rand() % 255;
//    arr[3] = rand() % 255;
//    arr[4] = rand() % 255;
//    int i = 0;
//    for(i = 0; i < 5; i++){
//        printf("i= %d\n", arr[i]);
//    }
    
    //char * input = read_file(0, "/Users/dilloncoffman/Desktop/Fall_2017/myfile.txt");
    write_file(0, "/Users/dilloncoffman/Desktop/tmp/test2.txt", "Woahh\n");
    read_file(0, "/Users/dilloncoffman/Desktop/tmp/test.txt");
    
    return 0;
}

char *read_file(int len, char *filename){
    FILE *ptrFile = fopen(filename, "r"); //open file for reading
    if(!ptrFile){ //if file does not exist
        fputs("Error: File not found.\n", stderr);
        exit(1);
    }
    
    if(len == 0){ //if length is 0, count length of file
//    int count = 0; //define a count to keep track of length of file, don't need for second part
        while(getc(ptrFile) != EOF){ //go through file until EOF read
            len++; //increment the size of file for each char read
        }
        rewind(ptrFile);
    }
    
    //mqlloc is in the stack, not heap
    char *string = (char*) malloc(len+1); //allocate memory for string input, plus one for null
    int j = 0;
    for(j = 0; j < len; j++){
        string[j] = getc(ptrFile);
        
    }
    string[j] = '\0';
    
    if(string == NULL){ //if there is no string to read
        fputs("No stringg to read.\n", stderr); //show error
        return NULL; //return nothing
    }
    
    printf("%s", string);
    
    fclose(ptrFile); //closes the file
    free(string); //frees the memory
    return string; //returns the string read to a file
}

void write_file(int len, char *filename, char *output){
    FILE *ptrFile = fopen(filename, "w"); //open file for reading
    if(ptrFile == NULL){
        printf("Error: File not opened.\n");
        exit(3);
    }
    
    int j = 0;
    if(len == 0){
        while(output[j] != '\0')
              putc(output[j++], ptrFile);
    } else {
        for(j=0; j < len; j++){
            putc(output[j], ptrFile);
        }
    }
    
    fclose(ptrFile);
    return;
}



//char *make_rand_key(int length, int *string){
//    
//    return string;
//}


