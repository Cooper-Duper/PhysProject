//Transforms the individual shader files into shader source strings that are stored in the "shaders.h" file
#include <stdio.h>
#include <stdlib.h>
#define STRING_GROW_SIZE 1024

char* getShaderString(char* sourceFileName);

int main(int argc, char** argv) {
    
    //Reading shaders based on command line input
    char* vertShaderSource = getShaderString(argv[1]); 
    char* fragShaderSource = getShaderString(argv[2]); 
    if (vertShaderSource == NULL || fragShaderSource == NULL) {
        puts("Error creating shader strings");
        return 1;
    }

    FILE* output = fopen("shaders.h", "w");
    if (output == NULL) {
        puts("Error opening output file");
        return 2;
    }

    //Writing to the output file
    fprintf(output, "const GLchar const * vertexSourceString = %s\nconst GLchar const * fragmentSourceString = %s\n", vertShaderSource, fragShaderSource);
    fclose(output);

    free(vertShaderSource);
    free(fragShaderSource);

    return 0;
}

//Kind of a scuffed interpreter / transpiler thing
char* getShaderString(char* sourceFileName) {
    
    FILE* sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL) {
        puts("Could not load shader file");
        return NULL;
    }
    char* sourceString = (char*) malloc(STRING_GROW_SIZE * sizeof(char));
    int stringLength = STRING_GROW_SIZE;
    //Needs to start with a quote
    sourceString[0] = '\"';
    //Index of the current working character
    int i = 1;
    char currChar;
    while ((currChar = fgetc(sourceFile)) != EOF) {
        //Growing array if needed
        if (stringLength < i + 5) {
            sourceString = (char*) realloc(sourceString, i + STRING_GROW_SIZE);
            stringLength += STRING_GROW_SIZE;
        }
        
        //Formatting at the end of a line if needed
        if (currChar == '\n') {
            sourceString[i] = '\\';
            sourceString[i + 1] = 'n';
            sourceString[i + 2] = '\"';
            sourceString[i + 3] = '\n';
            sourceString[i + 4] = '\"';
            i += 5;
        //Copying the character to the output if not
        } else {
            sourceString[i] = currChar;
            i++;
        }
    }
    
    //Don't need to trim as only the part until '\0' will be copied and not re-allocating will save some time technially...
    //Ending the string
    sourceString[i - 2] = ';';
    sourceString[i - 1] = '\0';
    return sourceString;
}
