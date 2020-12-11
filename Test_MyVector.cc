#include <iostream>
#include "./My_Vector.h"

int main(void){
    my_vector<double> test;
    test.resize(100, 10.2);
    test.resize(120);

}
