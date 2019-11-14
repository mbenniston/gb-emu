#include <stdio.h>
#include <string.h>

#include "../include/instructions.h"
#include "../include/registers.h"

/*
    Not a real assembler but a file that converts instructions to machine code
    used for the debugging of instructions 
*/

int main(int argc, char** argv) 
{
    if(argc < 3) return 1;

    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    if(!file) return 1;

    const char* outputFileName = argv[2];
    FILE* outfile = fopen(outputFileName, "wb");
    if(!outfile) return 1;

    char buffer[255];
    while(fgets(buffer, 255, file) != NULL) {
        for(int i = 0; i < sizeof(instruction_set) / sizeof(Instruction); i++) {
            if(instruction_set[i].name != NULL && strncmp(instruction_set[i].name, buffer, strlen(instruction_set[i].name)) == 0) { fwrite(&i, 1, 1, outfile); }
        }
    }

    fclose(file);
    fclose(outfile);

    return 0;
}