#include <iostream>

// Write a function to print a C-style string character by character. 
// Use a pointer and pointer arithmetic to step through each character ´
// of the string and print that character. 
void printString(const char* ptr) {
    while (static_cast<int>(*ptr) != 0) {
        std::cout << *ptr;
        ++ptr;
    }
}

// Repeat quiz #1, but this time the function should print the string backwards.
void printStringBackwards(const char* ptr) {
    const char* begin {ptr};

    // Traverse to the end of the string
    while (static_cast<int>(*ptr) != 0) {
        ++ptr;
    }

    // Traverse back to the beginning, printing each character
    while (ptr != begin) {
        // We start the loop at the terminating null character, so first decrement ptr.
        // This order also ensures we also print out the first character in the string.
        --ptr;  
        std::cout << *ptr;
    }
}


// Write a main function that tests the function with the string literal “Hello, world!”.
int main() {
    const char hello[] {"Hello, world!"};

    printString(hello);
    std::cout << '\n';

    printStringBackwards(hello);
    std::cout << '\n';

    return 0;
}

// Improvements from the tutorial's solutions:
// 1. No need to static_cast<int> the chars to compare them against 0.
// Just do *str != '\0'.
//
// 2. Declare function parameters as const char str[] instead of const char*.
//
// 3. For the printing backwards one, might be cleaner to leave the input pointer
// untouched and modify its copy.