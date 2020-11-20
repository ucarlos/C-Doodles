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
#include <cstdint>
#define VAL (64)
using namespace std;

int main(void){
    long double *list;
    
    const uint64_t temp = VAL * sizeof(long double);
    const uint64_t shift = (1 << 20);
    for (uint64_t i = 1; ; i++){ // Yeah no shit it's a endless loop compiler
	list = new long double[VAL];
	unsigned long long ll = i * temp;
	// long double ld = (ll / powl(2, 20));
	long double ld = (ll / (long double)(shift));
	cout << "Allocated " << ll << " bytes (" << ld << " MB)" << endl;
    }
}
