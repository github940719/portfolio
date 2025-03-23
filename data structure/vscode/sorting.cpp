#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;


void print(vector<int>& arr) {
    int previous = INT_MIN ;
    bool sorted = true ;
    for (auto i = arr.begin(); i != arr.end(); i++) {
        cout << (*i) << " " ;
        if ((*i) < previous) {
            sorted = false ;
        }
        previous = (*i) ;
    }

    if (sorted) {
        cout << "correctly sorted\n" ;
    }
    else {
        cout << "incorrectly sorted\n" ;
    }
}


void swap(int& a, int& b) {
    int temp = a ;
    a = b ;
    b = temp ;
}


void selectionSort(vector<int>& arr, int n) {  // not stable e.g. 3 1 2 3 1
    for (int i = 0; i < n-1; i++) {
        
        // find the minIndex from index = i to n-2
        // index = n-1 would be automatically sorted
        int minIndex = i ;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j ;
            }
        }
        
        swap(arr[i], arr[minIndex]) ;
    }
}


void bubbleSort(vector<int>& arr, int n) {
    for (int i = n-1; i > 0; i--) {

        bool sorted = true ;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]) ;
                sorted = false ;
            }
        }
        
        // at this time, arr[i] is the max of the previous subarray
        if (sorted) {
            return ;
        }
    }
}


void insertionSort(vector<int>& arr, int n) {
    // assume index = 0 to i-1 is sorted, then insert index = i to the right place
    for (int i = 1; i < n; i++) {
        int pivot = arr[i], j ;

        for (j = i-1; j >= 0; j--) {
            if (arr[j] > pivot) {
                arr[j+1] = arr[j] ;
            }
            else {
                break ;
            }
        }

        arr[j+1] = pivot ;
    }
}


void quickSort(vector<int>& arr, int left, int right) { // not stable
    if (left >= right) {
        return ;
    }

    int pivotIndex = left, i = left + 1, j = right ;
    do {
        while (i <= j && arr[i] <= arr[pivotIndex]) {
            i++ ;
        }
        while (i <= j && arr[j] >= arr[pivotIndex]) {
            j-- ;
        }
        if (i < j) {
            swap(arr[i], arr[j]) ;
        }
    } while (i < j) ;
    swap(arr[pivotIndex], arr[j]) ;

    quickSort(arr, left, j - 1) ;
    quickSort(arr, j + 1, right) ;
}


void merge(vector<int>& arr, int p, vector<int>& sub1, vector<int>& sub2) {
    int p1 = 0, p2 = 0 ;

    while (p1 < sub1.size() && p2 < sub2.size()) {
        if (sub1[p1] < sub2[p2]) {
            arr[p++] = sub1[p1++] ;
        }
        else {
            arr[p++] = sub2[p2++] ;
        }
    }

    while (p1 < sub1.size()) {
        arr[p++] = sub1[p1++] ;
    }
    while (p2 < sub2.size()) {
        arr[p++] = sub2[p2++] ;
    }
}


void mergeSortRecursion(vector<int>& arr, int left, int right) {  // memory
    if (left >= right) {
        return ;
    }

    // divide
    int mid = left + (right - left) / 2 ;
    mergeSortRecursion(arr, left, mid) ;
    mergeSortRecursion(arr, mid+1, right) ;

    // merge
    vector<int> sub1(arr.begin() + left, arr.begin() + mid + 1) ;
    vector<int> sub2(arr.begin() + mid + 1, arr.begin() + right + 1) ;
    merge(arr, left, sub1, sub2) ;
}


void mergeSortIteration(vector<int>& arr) {  // memory
    int size = arr.size() ;
    for (int len = 1; len < size; len *= 2) {
        for (int start = 0; start < size; start += (2 * len)) {
            int mid = min(start + len, size) ;
            int right = min(start + 2 * len, size) ;
            vector<int> sub1(arr.begin() + start, arr.begin() + mid) ;
            vector<int> sub2(arr.begin() + mid, arr.begin() + right) ;
            merge(arr, start, sub1, sub2) ; 
        }
    }
}


void radixSort(vector<int>& arr, int n) {  // memory

    // find the max element
    int maxValue = arr[0] ;
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i] ;
        }
    }

    for (int exp = 1; maxValue / exp > 0; exp *= 10) {

        // count
        vector<int> count(10, 0) ;
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10 ;
            count[digit]++ ;
        }

        // cummulate 
        for (int i = 1; i < 10; i++) {
            count[i] += count[i-1] ;
        }
        
        // calculate start index
        for (int i = 9; i > 0; i--) {
            count[i] = count[i-1] ;
        }
        count[0] = 0 ;

        // allocate
        vector<int> output = arr ;
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10 ;
            output[count[digit]++] = arr[i] ;
        }

        // copy the output to the original array
        arr = output ;
    }
}


void buildMaxHeap(vector<int>& arr, int root, int n) {
    while (2 * root + 1 < n) {
        int largerIndex = 2 * root + 1 ;  // left child
        if (largerIndex + 1 < n && arr[largerIndex + 1] > arr[largerIndex]) {
            largerIndex++ ;  // switch to right child
        }

        if (arr[root] < arr[largerIndex]) {  // move downward
            swap(arr[root], arr[largerIndex]) ;
            root = largerIndex ;
        }
        else {
            break ;  // find the correct position
        }
    }
}


void heapSort(vector<int>& arr, int n) {  // not stable
    for (int i  = (n - 1) / 2; i >= 0; i--) {  // for all internal nodes
        buildMaxHeap(arr, i, n) ;
    }

    for (int i = n-1; i > 0; i--) {
        swap(arr[i], arr[0]) ;  // so that arr[i] is the max of index = 0 to i-1
        buildMaxHeap(arr, 0, i) ;
    }
}



int main() {
    vector<int> original = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1} ;
    int n = original.size() ;

    vector<int> arr = original ;
    // selectionSort(arr, n) ;
    // print(arr) ;

    // arr = original ;
    // bubbleSort(arr, n) ;
    // print(arr) ;

    // arr = original ;
    // insertionSort(arr, n) ;
    // print(arr) ;

    // arr = original ;
    // quickSort(arr, 0, n-1) ;
    // print(arr) ;

    // arr = original ;
    // mergeSortRecursion(arr, 0, n-1) ;
    // print(arr) ;

    arr = original ;
    mergeSortIteration(arr) ;
    print(arr) ;

    // arr = original ;
    // heapSort(arr, n) ;
    // print(arr) ;

    // arr = original ;
    // radixSort(arr, n) ;
    // print(arr) ;

    return 0 ;
}
