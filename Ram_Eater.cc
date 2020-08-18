/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/01/2020 at 22:15
 * 
 * Problem17_06
 * Please don't run this. This basically causes a memory leak
 * to determine how much memory can be allocated before failing.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
#include <iomanip>
// #include <cmath>
#define VAL (32)
using namespace std;

int main(void){
    long double *list;
    unsigned long long temp = VAL * sizeof(long double);
    //cout << setprecision(4);
    for (unsigned long long i = 1; ; i++){ // Yeah no shit it's a endless loop compiler
	list = new long double[VAL];
	unsigned long long ll = i * temp;
	// long double ld = (ll / powl(2, 20));
	long double ld = (ll / (long double)(1 << 20));
	cout << "Allocated " << ll << " bytes ("
	     << ld << " MB)"
	     << endl;
    }

}
