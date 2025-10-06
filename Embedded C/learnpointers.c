// variable created in C, memory address assigned to variable, to access
// use reference operator &. result is where variable is stored

// a pointer is a variable that stores the memory address of another variable as its value 
// pointer variable points to a data type, created with * operator 



#include <stdio.h>

int main(){

    int testNum = 43;
    int* ptr = &testNum;   // ptr i a pointer variabe
    printf("%p", &testNum);         // &testNum is a pointer, stores memory address of testNum as its value
                                    // %p used for pointer type
    printf("\n %d", testNum);

    printf("\n %p ", ptr);

    // deference the pointer with *, get the value of the variable the pointer points to
    printf("\n %d", *ptr);


    // can also use pointers to access arrays
    int numbers[4] = {2, 5, 10, 12};

    for(int i = 0; i<sizeof(numbers)/sizeof(numbers[0]); i++){
        printf("\n %d", numbers[i]);
        printf("\n %p", &numbers[i]);
    }

    // in C the name of the array is a pointer to the first element in the array 

    printf("\n %p", &numbers);
    printf("\n %p", &numbers[0]);
    printf("\n %d", *numbers);
    printf("\n %d", *(numbers+1)); // second element]

    for(int i = 0; i<sizeof(numbers)/sizeof(numbers[0]); i++){
        printf("\n %d", *(numbers+i));
    }

    // change value
    *(numbers+1) =17;   // changes 5 to 17



    return 0;
}