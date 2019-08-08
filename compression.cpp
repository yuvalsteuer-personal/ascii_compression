/*
a   -   00000
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
\t  -   11110
EOF   - 11111
 */

#include "cstdio"
#include "string"
#include "cstdlib"
#include "cstdio"
#include <iostream>
#include <fstream>
#include <vector>

#define BYTE char
#define BIT_ZERO      1
#define BIT_ONE       2
#define BIT_TWO       4
#define BIT_THREE     8
#define BIT_FOUR     16
#define BIT_FIVE     32
#define BIT_SIX      64
#define BIT_SEVEN   128
// 00000000 01000100

BYTE compressCharacter(char chr); 
bool readFile(const std::string& fileName, std::string& fileContent);
std::vector<char> compressText(std::string& text);
int printInts(std::string str)
{
    std::cout << "\n";
    for(int i =0;i < str.length();++i)
    {
        printf("%d ", (size_t)str[i]);
    }
    std::cout << "\n";
    return 0;
}

int main()
{
    std::string fileText;
    bool size=readFile("text", fileText);
    std::cout << "Before: " << fileText << std::endl;
    auto v = compressText(fileText);
    std::string str(v.begin(), v.end());
    std::cout << "compressed: \n" << printInts(str) << '\n'; 
    return 0;
}

std::vector<char> compressText(std::string& text)
{
    size_t length = text.length();
    char compressedChar;
    std::vector<BYTE> compressedText;
    compressedText.resize((size_t)(length*(5/8)+1)); // from 8 bits to 5 bits a character.
    compressedText[0] = '\0';
    for(int i = 0,j = 0;i<length;++i)
    {
        compressedChar = compressCharacter(text[j]);
        compressedText[i] = compressedChar << 3;
        if(j+1< length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;
        
        compressedText[i] |= compressedChar >> 2;
        compressedText.push_back('\0');
        ++i;
        compressedText[i] |= compressedChar << 6;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;

        compressedText[i] |= compressedChar << 1;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;

        compressedText[i] |= compressedChar >> 4;
        compressedText.push_back('\0');
        ++i;
        compressedText[i] |= compressedChar << 4;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;
        
        compressedText[i] |= compressedChar >> 1;
        compressedText.push_back('\0');
        ++i;
        compressedText[i] |= compressedChar << 7;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;
        
        compressedText[i] |= compressedChar << 2;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;

        compressedText[i] |= compressedChar >> 3;

        compressedText.push_back('\0');
        ++i;

        compressedText[i] |= compressedChar << 5;

        if(j+1 < length){
            ++j;
            compressedChar = compressCharacter(text[j]);
        }
        else
            return compressedText;

        compressedText[i] |= compressedChar;
    }
}
bool readFile(const std::string& fileName, std::string& fileContent)
{
    char c;
    std::ifstream inputFile;
    inputFile.open(fileName);
    if(!inputFile)
    {
        std::cerr << "Unable to open file datafile.txt\n";
        exit(1);   // call system to stop
    }
    while(inputFile.get(c)){
        fileContent += c;
    }
    return true;
}
BYTE compressCharacter(char chr)
{
    BYTE byte = 0;
    // you can also just do: chr - 'a' for alphabetic characters and just add more cases.
    switch(chr){
        case 'a':
        case 'A':
            byte = 0;
            break;
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
        
        case '\t':
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ONE);
            break;
        case EOF:
            byte = (BYTE)(BIT_FOUR | BIT_THREE | BIT_TWO | BIT_ONE | BIT_ZERO);
            break;


    }
    return byte;
}