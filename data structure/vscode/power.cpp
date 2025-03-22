#include <iostream>
using namespace std;


long long int recursion (int x, int n) {
    if (n == 0) {
        return 1 ;
    }
    return x * recursion(x, n-1) ;
}


long long int iteration(int x, int n) {
    long long int ans = 1 ;
    for (int i = 0; i < n; i++) {
        ans *= x ;
    }
    return ans ;
}


long long int fastPower(int x, int n) {
    long long int ans = 1 ;
    while (n) {  // n != 0
        if (n % 2) {  // n is odd
            ans *= x ;
        }
        n /= 2 ;
        x *= x ;
    }
    return ans ;
}


long long int fastPowerBitwise(int x, int n) {
    long long int ans = 1 ;
    while (n) {  // n != 0
        if (n & 1) {  // n is odd
            ans *= x ;
        }
        n >>= 1 ;  // n /= 2 (shift right)
        x *= x ;
    }
    return ans ;  
}


long long int naivePolynomial(int x, int n, int* coef) {
    long long int ans = coef[0], power = x ;
    for (int i = 1; i <= n; i++) {
        ans += (coef[i] * power) ;
        power *= x ;
    }
    return ans ;
}


long long int fastPolynomial(int x, int n, int* coef) {

    // e.g. P(x, n = 4) = a0 + x {a1 + x [a2 + x (a3 + x * a4)]}
    long long int ans = coef[n] ;  // highest coefficient
    for (int i = n-1; i >= 0; i--) {  // from high to low
        ans *= x ;
        ans += coef[i] ;
    }
    return ans ;
}


int main() {
    int x, n ;
    cin >> x >> n ;
    cout << recursion(x, n) << endl ;
    cout << iteration(x, n) << endl ;
    cout << fastPower(x, n) << endl ;
    cout << fastPowerBitwise(x, n) << endl ;

    int* coef = new int[n+1] ;
    for (int i = 0; i <= n; i++) {
        coef[i] = i + 1 ;
    }

    cout << naivePolynomial(x, n, coef) << endl ;
    cout << fastPolynomial(x, n, coef) << endl ;
    return 0 ;
}