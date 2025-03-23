#include <iostream>
using namespace std;


int main() {
    int arr[10][20][30] ;
    int index[3] = {5, 6, 9} ;
    int dim[3] = {10, 20, 30} ;
    cout << (&arr[index[0]][index[1]][index[2]] - &arr[0][0][0]) << endl ;


    int address = 0, cummuDimention = 1 ;
    for (int i = 2; i >= 0; i--) {  // O(n) rather than O(n^2)
        address += (index[i] * cummuDimention) ;
        cummuDimention *= dim[i] ;
    }
    cout << address << endl ;
}