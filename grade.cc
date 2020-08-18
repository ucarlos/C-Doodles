#include <iostream>
using namespace std;

char get_grade(int &val){
    if (!(0 <= val && val <= 100))
	return '\b';
    
    char result;
    int ten = val / 10;
    int ones = val % 10;
    switch (ten){
    default:
	return 'F';
    case 7:
	switch (ones){
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	    return 'D';
	default:
	    return 'C';

	}
    case 8:
	return 'B';
    case 9:
    case 10:
	return 'A';
	
    }

}


int main(void){
    int grade = 74;
    cout << "Grade : " << get_grade(grade) << "\n";
    
}
