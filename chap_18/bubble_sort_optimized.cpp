#include <iostream>
#include <utility> // for std::swap()
#include <iterator> // for std::size()

int main() {
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length { static_cast<int>(std::size(array)) };

    // optimization: check if no swaps are done for an entire iteration
    bool noSwaps{false};
    int iteration{0};
    
    for (; iteration < length - 1; ++iteration) {
        noSwaps = true;
        // optimization: at every iteration, we guarantee that the last item is sorted
        for (int j {0}; j < length - iteration - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                noSwaps = false;
            }
        }
        if (noSwaps) {
            break;
        }
    }

    if (iteration < length - 1) {
        std::cout << "Early termination on iteration " << iteration + 1 << '\n';
    }

    // Now print our sorted array as proof it works
    for (int index{ 0 }; index < length; ++index)
        std::cout << array[index] << ' ';

    std::cout << '\n';
}