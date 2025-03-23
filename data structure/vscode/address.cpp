#include <iostream>
using namespace std;


int main() {
    int arr[10][20][30] ;
    int index[3] = {5, 6, 9} ;
    int dim[3] = {10, 20, 30} ;
    cout << (&arr[index[0]][index[1]][index[2]] - &arr[0][0][0]) << endl ;

    // O(n) (for future use)
    int remain[3] = {0, 0, 1} ;
    for (int i = 3-1; i > 0; i--) {
        remain[i-1] = remain[i] * dim[i] ;
    }

    // O(n)
    int address = 0 ;
    for (int i = 0; i < 3; i++) {
        address += (index[i] * remain[i]) ;
    }
    cout << address << endl ;
}
