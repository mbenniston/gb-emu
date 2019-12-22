#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/instructions.h"
#include "../include/registers.h"

/*
    Not a real assembler but a file that converts instructions to machine code
    used for the debugging of instructions 
*/

int main(int argc, char** argv) 
{
    if(argc < 3) {
        if(argc == 2 && strcmp("-l", argv[1]) == 0) {
            
            for(int i = 0; i < sizeof(instruction_set) / sizeof(Instruction); i++) {
                if(instruction_set[i].name != NULL) puts(instruction_set[i].name);
            }

            return 0;
        }
        return 1;
    }
    if(strcmp("-d", argv[2]) == 0) {
        const char* fileName = argv[1];
        FILE* file = fopen(fileName, "rb");
        if(!file) return 1;

        int c;
        int i = 0;
        int immCount = 0;
        while((c = fgetc(file)) != EOF) {
            byte b = c;

            if(immCount > 0) {
                printf("0x%X: #0x%X\n", i, b);
                immCount--;
            } else {
                if(instruction_set[b].name != NULL) {
                    printf("0x%X: 0x%X, %s\n", i, b, instruction_set[b].name);
                    immCount += instruction_set[b].numImmediates;
                } else {
                    printf("0x%X: 0x%X, %s\n", i, b, "Unknown instruction");
                }
            }

            i++;
        }

        for(int i = 0; i < 16; i++) {
                    }

    } else {
        const char* fileName = argv[1];
        FILE* file = fopen(fileName, "r");
        if(!file) return 1;

        const char* outputFileName = argv[2];
        FILE* outfile = fopen(outputFileName, "wb");
        if(!outfile) return 1;

        bool instFound;
        char buffer[255];
        while(fgets(buffer, 255, file) != NULL) {
            instFound = false;

            for(int i = 0; i < sizeof(instruction_set) / sizeof(Instruction); i++) {
                if(instruction_set[i].name != NULL && strncmp(instruction_set[i].name, buffer, strlen(instruction_set[i].name)) == 0) { 
                    fwrite(&i, 1, 1, outfile); 
                    instFound = true;
                } 
            }

            if(instFound == false) {
                char* pEnd;
                unsigned int data = strtoll(buffer, &pEnd, 16);
                if(data != 0 || buffer[0] == '0') {
                    unsigned char datab = data & 0xFF;
                    fwrite(&datab, 1, 1, outfile); 
                } else {
                    printf("Unknown instruction: %s\n", buffer);
                    return 1;
                }
            }
        }

        fclose(file);
        fclose(outfile);
    }

    

    return 0;
}