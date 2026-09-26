#include <iostream>
#include <utility> // for std::swap()
#include <iterator> // for std::size()

int main() {
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length { static_cast<int>(std::size(array)) };
    
    for (int i {0}; i < length - 1; ++i) {
        for (int j {0}; j < length - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }

    // Now print our sorted array as proof it works
    for (int index{ 0 }; index < length; ++index)
        std::cout << array[index] << ' ';

    std::cout << '\n';
}