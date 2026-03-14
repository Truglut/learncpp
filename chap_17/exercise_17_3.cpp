#include <array>
#include <iostream>


// Complete the program by defining printArray
template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr) // pass by const reference
{
    if (N == 0)
    {
        std::cout << "The array () has 0 elements";
        return;
    }

    std::cout << "The array (" << arr[0];

    // Print out array elements
    for (int i = 1; i < N; i++) 
    {
        std::cout << ", " << arr[i]; 
    }

    // // Intelligent solution in the tutorial:
    // auto separator {""};
    // for (const auto& e: arr)
    // {
    //     std::cout << separator << e;
    //     separator = ", ";
    // }

    // Close parenthesis and print length
    std::cout << ") has length " << N << ".\n";
}


int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}