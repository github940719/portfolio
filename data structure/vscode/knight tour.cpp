#include <iostream>
#include <iomanip>
using namespace std;


// 8 different directions to walk toward
int nextX[8] = {2, 2, 1, -1,-2, -2, -1, 1} ;
int nextY[8] = {-1, 1, 2, 2, 1, -1, -2, -2} ;


void print(int** square, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(3) << square[i][j] ;
        }
        cout << endl ;
    }  
}


bool validPosition(int size, int** square, int x, int y) {
    return (x >= 0 && y >= 0 && x < size && y < size && square[x][y] == 0) ;
}


int possibleWayCnt(int size, int** square, int startX, int startY) {
    int ans = 0 ;
    for (int i = 0; i < 8; i++) {
        int x = startX + nextX[i], y = startY + nextY[i] ;
        if (validPosition(size, square, x, y)) {
            ans++ ;
        }
    }
    return ans ;
}


void knightTour(int size, int startX, int startY, int** square) {
    square[startX][startY] = 1 ;
    for (int i = 2; i <= size * size; i++) {  // for the i^th step
        int leastIndex = -1, leastCnt = 0 ;
        for (int j = 0; j < 8; j++) {  // for all next direction
            if (!validPosition(size, square, startX + nextX[j], startY + nextY[j])) {  
                continue ;  // ignore invalid direction
            }
            // find the valid next way count of this direction
            int nextWayCnt = possibleWayCnt(size, square, startX + nextX[j], startY + nextY[j]) ;
            if (leastIndex == -1) {  // choose this first valid way
                leastIndex = j ;
                leastCnt = nextWayCnt ;
            }
            else if (nextWayCnt > 0 && (leastCnt == 0 || nextWayCnt < leastCnt)) {  // choose this way (with least number of next valid way but > 0)
                leastIndex = j ;
                leastCnt = nextWayCnt ;
            }
        }

        // check whether the knight stuck here
        if (leastIndex == -1) {
            cout << "step = " << i << " stuck at x = " << startX << ", y = " << startY << endl ;
            return ;
        }

        // move
        startX += nextX[leastIndex] ;
        startY += nextY[leastIndex] ;
        square[startX][startY] = i ;
    }
}


int main() {
    int size, startX, startY ;
    cin >> size >> startX >> startY ;

    // initialize
    int** square = new int*[size] ;
    for (int i = 0; i < size; i++) {
        square[i] = new int[size] ;
        for (int j = 0; j < size; j++) {
            square[i][j] = 0 ;
        }
    }

    knightTour(size, startX, startY, square) ;
    print(square, size) ;
    return 0 ;
}
