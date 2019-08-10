/*
b   -   00001
c   -   00010
d   -   00011
e   -   00100
f   -   00101
g   -   00110
h   -   00111
i   -   01000
j   -   01001
k   -   01010
l   -   01011
m   -   01100
n   -   01101
o   -   01110
p   -   01111
q   -   10000
r   -   10001
s   -   10010
t   -   10011
u   -   10100
v   -   10101
w   -   10110
x   -   10111
y   -   11000
z   -   11001
' ' -   11010
,   -   11011
.   -   11100
\n  -   11101
a  -    11110
EOF   - 11111
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BYTE unsigned char
#define BIT_ZERO                        1
#define BIT_ONE                         2
#define BIT_TWO                         4
#define BIT_THREE                       8
#define BIT_FOUR                       16
#define BIT_FIVE                       32
#define BIT_SIX                        64
#define BIT_SEVEN                     128

#define NUMBER_OF_ACCEPTED_ARGS         4
#define OPTION_INDEX                    1
#define INPUT_FILE_INDEX                2
#define OUTPUT_FILE_INDEX               3

#define TRUE 1
#define FALSE 0
#define BOOL char

BYTE compressCharacter(char chr); 

char decompressByte(BYTE byte);
char* readFile(const char * fileName, int* error, size_t* fileSize);


void usage(void);
void writeToFile(const char* fileName, char* fileContent, size_t length);

size_t compressText(char* text, size_t textLength, char** compressedText);
size_t decompressText(char* arr, size_t arrLength, char** decompressedText);


int main(int argc, char** argv)
{
    if(argc != NUMBER_OF_ACCEPTED_ARGS){
        printf("\nERROR! Wrong usage!\n\n");
        usage();
        exit(1);
    }
    char* text = NULL;
    int* error;
    size_t length;
    text = readFile(argv[INPUT_FILE_INDEX], error, &length);
    if(strcmp(argv[OPTION_INDEX], "-c") == 0 || strcmp(argv[OPTION_INDEX], "--compress") == 0){
        char* compressedText = NULL;
        size_t compressedLength = compressText(text,length, &compressedText);
        writeToFile(argv[OUTPUT_FILE_INDEX], compressedText,  compressedLength);
    }
    else if(strcmp(argv[OPTION_INDEX], "-d") == 0 || strcmp(argv[OPTION_INDEX], "--decompress") == 0){
        char* decompressedText = NULL;
        size_t decompressedLength = decompressText(text, length, &decompressedText);
        writeToFile(argv[OUTPUT_FILE_INDEX], decompressedText,  decompressedLength);
    }
    else
    {
        printf("\nERROR! Wrong usage!\n\n");
        usage();
        exit(1);
    }
    return 0;
}
void usage(void)
{
    printf("\nNAME:\n\tcompressor - compresses/decompresses ascii alphabetic files.\nSYNOPSIS:\n\tcompressor [OPTION] [INPUT_FILE] [OUTPUT_FILE]\n");
    printf("\nDESCRIPTION:\n\tcompresses/decompresses ascii encoded file containing alphabetical characters...\n");
    printf("OPTIONS:\n\t(-c, --compress): compresses file and outputs into FILE\n");
    printf("\t(-d, --decompress): decompresses file and outputs into FILE\n\n\n");
}
void writeToFile(const char* fileName, char* fileContent, size_t length)
{
    FILE* fp = fopen(fileName, "w+");
    if(!fp)
    {
        fprintf(stderr, "Unable to open file %s\n", fileName);
        exit(1);   // call system to stop
    }
    for(int i = 0;i < length;++i)
    {
        fputc(fileContent[i],fp);
    }
    fclose(fp);
}
size_t decompressText(char* arr, size_t arrLength, char** decompressedText)
{
    BYTE byte = '\0', byte2 = '\0';
    size_t j = 0;
    *decompressedText = (char*)malloc(1024);
    for(size_t i = 0;i<arrLength;++i)
    {
        byte = arr[i] >> 3;
        *decompressedText[j] = decompressByte(byte);
        j++;
        //string.push_back(decompressByte(byte));

        byte = (arr[i] << 5);
        byte >>= 3;
        if(i+1 < arrLength){
            ++i;
        }
        else{
            return j;
        }
        byte2 = arr[i] >> 6;
        byte = byte | byte2;
        *decompressedText[j] = decompressByte(byte);
        j++;
        // string.push_back(decompressByte(byte));

        byte = (arr[i] << 2);
        byte >>= 3;
        *decompressedText[j] = decompressByte(byte);
        j++;
        //string.push_back(decompressByte(byte));

        byte = (arr[i] << 7);
        byte >>= 3;
        if(i+1 < arrLength){
            ++i;
        }
        else{
            return j;
        }
        byte2 = (arr[i] >> 4);
        byte = byte | byte2;
        *decompressedText[j] = decompressByte(byte);
        ++j;
        //string.push_back(decompressByte(byte));

        byte = (arr[i] << 4);
        byte >>= 3;
        if(i+1 < arrLength){
            ++i;
        }
        else{
            return j;
        }
        byte2 = arr[i] >> 7;
        byte = byte | byte2;
        *decompressedText[j] = decompressByte(byte);
        ++j;
        //string.push_back(decompressByte(byte));

        byte = (arr[i] << 1);
        byte >>= 3;
        *decompressedText[j] = decompressByte(byte);
        ++j;
        //string.push_back(decompressByte(byte));

        byte = (arr[i] << 6);
        byte >>= 3;
        if(i+1 < arrLength){
            ++i;
        }
        else{
            return j;
        }
        byte2 = arr[i] >> 5;
        byte = byte | byte2;
        *decompressedText[j] = decompressByte(byte);
        ++j;
        //string.push_back(decompressByte(byte));

        byte = (arr[i] << 3);
        byte >>=3;
        *decompressedText[j] = decompressByte(byte);
        ++j;
        //string.push_back(decompressByte(byte));
    }
    
    return j;
}
size_t compressText(char* text, size_t textLength, char** compressedText)
{
    size_t length = textLength;
    *compressedText = (char*)malloc(1024);
    char compressedChar = '\0';
    //compressedText.resize((size_t)(length*(5/8)+1)); // from 8 bits to 5 bits a character.
    BOOL firstTime = TRUE; 
    size_t i = 0, j =0;
    for(i = 0,j = 0;i<length;++i)
    {
        if(firstTime){
            firstTime = FALSE;
        }
        else{
            if(i+1<length)
                *compressedText[i+1] = '\0';
        }
        
        compressedChar = compressCharacter(text[j]);
        *compressedText[i] = compressedChar << 3;
        if(j+1< length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;
        
        *compressedText[i] |= compressedChar >> 2;
        ++i;
        *compressedText[i] = '\0';
        *compressedText[i] |= compressedChar << 6;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;

        *compressedText[i] |= compressedChar << 1;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;

        *compressedText[i] |= compressedChar >> 4;
        ++i;
        *compressedText[i] = '\0';
        *compressedText[i] |= compressedChar << 4;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;
        
        *compressedText[i] |= compressedChar >> 1;
        ++i;
        *compressedText[i] = '\0';
        *compressedText[i] |= compressedChar << 7;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;
        
        *compressedText[i] |= compressedChar << 2;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;

        *compressedText[i] |= compressedChar >> 3;

        ++i;
        *compressedText[i] = '\0';
        *compressedText[i] |= compressedChar << 5;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return i;

        *compressedText[i] |= compressedChar;
        if(j+1 < length){
            ++j;
        }
        else
            return i;
    }
    return i;
}

char* readFile(const char * fileName, int* error, size_t* fileSize) {
    char * buffer = '\0';
    size_t length = 0;
    FILE* f = fopen(fileName, "rb");
    size_t readLength = 0;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = (char*)malloc(length + 1);

        if (length) {
            readLength = fread(buffer, 1, length, f);

            if (length != readLength) {
                 *error = 1;

                 return NULL;
            }
        }

        fclose(f);

        *error = 1;
        buffer[length] = '\0';
        *fileSize = length;
    }
    else {
        *error = 1;

        return NULL;
    }
    return buffer;
}
BYTE compressCharacter(char chr)
{
    BYTE byte = 0;
    // you can also just do: chr - 'a' for alphabetic characters and just add more cases.
    switch(chr){
        case 'b':
        case 'B':
            byte = (BYTE)(BIT_ZERO);
            break;
        case 'c':
        case 'C':
            byte = (BYTE)(BIT_ONE);
            break;
        case 'd':
        case 'D':
            byte = (BYTE)(BIT_ONE | BIT_ZERO);
            break;
        
        case 'e':
        case 'E':
            byte = (BYTE)(BIT_TWO);
            break;
        
        case 'f':
        case 'F':
            byte = (BYTE)(BIT_TWO | BIT_ZERO);
            break;
        
        case 'g':
        case 'G':
            byte = (BYTE)(BIT_TWO | BIT_ONE);
            break;
        
        case 'h':
        case 'H':
            byte = (BYTE)(BIT_TWO | BIT_ONE | BIT_ZERO);
            break;
        
        case 'i':
        case 'I':
            byte = (BYTE)(BIT_THREE);
            break;
        
        case 'j':
        case 'J':
            byte = (BYTE)(BIT_THREE | BIT_ZERO);
            break;
        
        case 'k':
        case 'K':
            byte = (BYTE)(BIT_THREE | BIT_ONE);
            break;
        
        case 'l':
        case 'L':
            byte = (BYTE)(BIT_THREE | BIT_ONE | BIT_ZERO);
            break;
        
        case 'm':
        case 'M':
            byte = (BYTE)(BIT_THREE | BIT_TWO);
            break;
        
        case 'n':
        case 'N':
            byte = (BYTE)(BIT_THREE | BIT_TWO | BIT_ZERO);
            break;
        
        case 'o':
        case 'O':
            byte = (BYTE)(BIT_THREE | BIT_TWO | BIT_ONE);
            break;
        
        case 'p':
        case 'P':
            byte = (BYTE)(BIT_THREE | BIT_TWO | BIT_ONE | BIT_ZERO);
            break;
        
        case 'q':
        case 'Q':
            byte = (BYTE)(BIT_FOUR);
            break;
        
        case 'r':
        case 'R':
            byte = (BYTE)(BIT_FOUR | BIT_ZERO);
            break;
        
        case 's':
        case 'S':
            byte = (BYTE)(BIT_FOUR | BIT_ONE);
            break;
        
        case 't':
        case 'T':
            byte = (BYTE)(BIT_FOUR | BIT_ONE | BIT_ZERO);
            break;
        
        case 'u':
        case 'U':
            byte = (BYTE)(BIT_FOUR | BIT_TWO);
            break;
        
        case 'v':
        case 'V':
            byte = (BYTE)(BIT_FOUR | BIT_TWO | BIT_ZERO);
            break;
        
        case 'w':
        case 'W':
            byte = (BYTE)(BIT_FOUR | BIT_TWO | BIT_ONE);
            break;
        
        case 'x':
        case 'X':
            byte = (BYTE)(BIT_FOUR | BIT_TWO | BIT_ONE | BIT_ZERO);
            break;
        
        case 'y':
        case 'Y':
            byte = (BYTE)(BIT_FOUR | BIT_THREE);
            break;
        
        case 'z':
        case 'Z':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_ZERO);
            break;

        case ' ':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_ONE);
            break;
        
        case ',':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_ONE | BIT_ZERO);
            break;
        
        case '.':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO);
            break;
        
        case '\n':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ZERO);
            break;
        
        case 'a':
        case 'A':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ONE);
            break;
        case EOF:
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ONE | BIT_ZERO);
            break;


    }
    return byte;
}
char decompressByte(BYTE byte)
{
    char chr = '\0';
    switch(byte)
    {
        case 0:
            chr = 'a';
            break;
        
        case (BYTE)(BIT_ZERO):
            chr = 'b';
            break;
        case (BYTE)(BIT_ONE):
            chr = 'c';
            break;
        case (BYTE)(BIT_ONE | BIT_ZERO):
            chr = 'd';
            break;
        
        case (BYTE)(BIT_TWO):
            chr = 'e';
            break;
        
        case (BYTE)(BIT_TWO | BIT_ZERO):
            chr = 'f';
            break;
        
        case (BYTE)(BIT_TWO | BIT_ONE):
            chr = 'g';
            break;
        
        case (BYTE)(BIT_TWO | BIT_ONE | BIT_ZERO):
            chr = 'h';
            break;
        
        case (BYTE)(BIT_THREE):
            chr = 'i';
            break;
        
        case (BYTE)(BIT_THREE | BIT_ZERO):
            chr = 'j';
            break;
        
        case (BYTE)(BIT_THREE | BIT_ONE):
            chr = 'k';
            break;
        
        case (BYTE)(BIT_THREE | BIT_ONE | BIT_ZERO):
            chr = 'l';
            break;
        
        case (BYTE)(BIT_THREE | BIT_TWO):
            chr = 'm';
            break;
        
        case (BYTE)(BIT_THREE | BIT_TWO | BIT_ZERO):
            chr = 'n';
            break;
        
        case (BYTE)(BIT_THREE | BIT_TWO | BIT_ONE):
            chr = 'o';
            break;
        
        case (BYTE)(BIT_THREE | BIT_TWO | BIT_ONE | BIT_ZERO):
            chr = 'p';
            break;
        
        case (BYTE)(BIT_FOUR):
            chr = 'q';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_ZERO):
            chr = 'r';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_ONE):
            chr = 's';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_ONE | BIT_ZERO):
            chr = 't';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_TWO):
            chr = 'u';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_TWO | BIT_ZERO):
            chr = 'v';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_TWO | BIT_ONE):
            chr = 'w';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_TWO | BIT_ONE | BIT_ZERO):
            chr = 'x';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_THREE):
            chr = 'y';
            break;

        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_ZERO):
            chr = 'z';
            break;

        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_ONE):
            chr = ' ';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_ONE | BIT_ZERO):
            chr = ',';
            break;

        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO):
            chr = '.';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ZERO):
            chr = '\n';
            break;
        
        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ONE):
            chr = 'a';
            break;
        case (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ONE | BIT_ZERO):        
            chr = EOF;
            break;
    }
    return chr;
}