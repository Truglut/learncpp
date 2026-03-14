#include <array>
#include <iostream>

int main()
{
    // Initialize the array (using CTAD to deduce type and length)
    constexpr std::array arr {'h', 'e', 'l', 'l', 'o'};

    // Print length of array
    std::cout << "The length is " << arr.size() << '\n';

    // Print element with index 1 with various methods
    std::cout << arr[1];
    std::cout << arr.at(1);
    std::cout << std::get<1>(arr) << '\n';
}