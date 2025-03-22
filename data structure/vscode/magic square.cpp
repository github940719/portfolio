#include <iostream>
#include <iomanip>
using namespace std;


void print(int** square, int size) {
    // set enough width (depending on the digit of size * size)
    int width = 1 ;
    for (int temp = size * size; temp > 0; temp /= 10, width++) {}

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(width) << square[i][j] << " " ;
        }
        cout << endl ;
    }
}


bool check(int** square, int size) {
    int sum = (1 + size * size) * size / 2 ;

    // check row and column sum
    for (int i = 0; i < size; i++) {
        int tempRow = 0, tempCol = 0 ;
        for (int j = 0; j < size; j++) {
            tempRow += square[i][j] ;
            tempCol += square[j][i] ;
        }
        if (tempRow != sum || tempCol != sum) {
            return false ;
        }
    }

    // check diagonal sum
    int temp1 = 0, temp2 = 0 ;
    for (int i = 0; i < size; i++) {
        temp1 += square[i][i] ;
        temp2 += square[i][size-i-1] ;
    }
    if (temp1 != sum || temp2 != sum) {
        return false ;
    }

    return true ;
}


void magicOdd(int** square, int size) {  // n is odd

    /*  if move left-top or right-top:
            start from top-middle
            move downward when conflict
        if move left-bottom or right-bottom:
            start from bottom-middle
            move upward when conflict
    */

    // traverse
    int i = 0, j = (size - 1) / 2 ;
    square[i][j] = 1 ;
    for (int n = 2; n <= size * size; n++) {
        int nextI = (i - 1 + size) % size ;  // move upward
        int nextJ = (j - 1 + size) % size ;  // move leftward
        if (square[nextI][nextJ]) {  // if a number has occupied this position
            i = (i + 1) % size ;  // move downward
        }
        else {
            i = nextI ;
            j = nextJ ;
        }
        square[i][j] = n ;
    }
}


void magic4(int** square, int size) {  // n = 4k
    // fill in 1, 2, ..., size*size from left to right, top to bottom
    int num = 1 ;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { 
            if ((i % 4 == j % 4) || ((i + j + 1) % 4 == 0)) {
                /*
                exception: on the left top to right bottom, or left bottom to right top diagonal
                swap square[i][j] and square[size - i - 1][size - j - 1]
                */
                square[i][j] = (1 + size * size) - num ;
            }
            else {
                square[i][j] = num ;
            }
            num++ ;
        }
    }
}


void swap(int& a, int& b) {  // for magic2
    int temp = a ;
    a = b ;
    b = temp ;
}


void magic2(int** square, int size) {  // n = 4k + 2 : Strachey method
    /*  
    seperate the square into 4 odd-n square as below:
    A C
    D B
    */

    // generate A as a square matric (odd-length)
    int half = size / 2 ;
    magicOdd(square, half) ;

    // B, C, D: corresponding cell in A + (1 or 2 or 3) * (falf * half)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            square[i + half][j + half] = square[i][j] + half * half ;  // B
            square[i][j + half] = square[i][j] + 2 * half * half ;  // C
            square[i + half][j] = square[i][j] + 3 * half * half ;  // D
        }
    }

    // swap some position of A and B, C and D
    int quarter = half / 2 ;
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < quarter; j++) {
            // exchange the leftmost "quarter" columns (A and D)  
            swap(square[i][j], square[half + i][j]) ;
        }
        for (int j = 0; j < quarter - 1; j++) {    
            // exchange the rightmost "quarter - 1" (B and C)
            swap(square[i][size - 1 - j], square[half + i][size - 1 - j]) ;
        }
        
        // Exchange the middle cell of the leftmost column (A and D)
        swap(square[quarter][0], square[quarter + half][0]) ;

        // Exchange the central cell in A and D
        swap(square[quarter][quarter], square[quarter + half][quarter]) ;
    }
}


int main() {

    // initialize
    int size ;
    cin >> size ;
    int** square = new int*[size] ;
    for (int i = 0; i < size; i++) {
        square[i] = new int[size] ;
        for (int j = 0; j < size; j++) {
            square[i][j] = 0 ;
        }
    }

    // create magic square, print, and then check
    if (size <= 0) {
        cout << "fail\n\n" ;
    }
    else if (size % 2 == 1) {
        magicOdd(square, size) ;
    }
    else if (size % 4 == 0) {
        magic4(square, size) ;
    }
    else {
        magic2(square, size) ;
    }
    print(square, size) ;
    if (check(square, size)) {
        cout << "correct\n\n" ;
    }
    else  {
        cout << "incorrect\n\n" ;
    }

    // delete the memory of the dynamic subarray
    for (int i = 0; i < size; i++) {
        delete [] square[i] ;
        square[i] = nullptr ;
    }
    delete [] square ;
    square = nullptr ;
    return 0 ;
}
