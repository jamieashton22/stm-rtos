// struct - group related variables in one data type

#include <stdio.h>
#include <string.h>

struct testStruct {
    int number;
    char letter;
    char string[30];    // mem needs to be allocated at run time so need to provide fixed size for string
};

int main(){

    struct testStruct struct1;      // declare variable of type testStruct
    struct testStruct struct2 = {2, 'b', "some text"};      // can also assign values when variable declared 
    
    struct1.number = 4;
    struct1.letter = 'a';
    strcpy(struct1.string, " a name ");     // need to use strcpy to assign 

    printf("Number %i \n", struct1.number);
    printf("Letter %c \n", struct1.letter);
    printf("string %s ", struct1.string);
    
    printf("\n %i, %c, %s", struct2.number, struct2.letter, struct2.string);
    

    
    return 0;
}