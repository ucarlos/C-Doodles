/*
 * -------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 12/08/2023 at 10:30 PM
 *
 * Foo.cc
 *
 * -------------------------------------------------------------------------------
 */

#include <iostream>
#include <memory>

class Example {
public:
    Example() = default;
private:
    int val{};
};

int main(void) {
    std::unique_ptr<int> int_pointer {new int{}};

    std::cout << "Initial Value: " << *int_pointer << "\n";

    for (int i = 0; i < 100; i++) {
        *int_pointer += 10;
    }
    std::cout << "Final Value: " << *int_pointer << "\n";


}


