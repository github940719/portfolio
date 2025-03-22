//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "sorting.h"
#include <time.h>
#include <cstdlib>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int n, range, step, repetition, decimalPlaces ;
int* originalData = nullptr ;
int* data = nullptr ;
bool randomNumberGenerated = false ;  // if false, we can not sort or search
bool sorted = false ;  // if false, we can not binary search
#define swap(x,y) {int t ; t = x ; x = y ; y = t ;}


// declare Time arrays, which would keep CPU time (sec.)
double* selectionSortTime = nullptr;
double* bubbleSortTime = nullptr;
double* quickSortTime = nullptr;
double* insertionSortTime = nullptr ;
double* mergeSortTime = nullptr ;
double* heapSortTime = nullptr ;


// generate random numbers
void generateRandomNumbers(int*& originalData, int size, int range) {
	if (originalData) {  // if original != nullptr
		delete [] originalData ;
	}

	originalData = new int[size] ;
	for (int i = 0; i < size; i++){
		originalData[i] = rand() % range + 1 ;  // 1 to range
	}

	randomNumberGenerated = true ;  // to avoid sort / search when data is not generated
	sorted = false ;  // to avoid binary search when data is not sorted
}


// if sort or search without random number generated, warning would be given in the corresponding memo
bool checkGenerated(TMemo* memo) {
	if (!randomNumberGenerated) {
		memo->Lines->Clear() ;
		memo->Lines->Add("Please press Generate Random Numbers first !") ;
		return false ;
	}
	return true ;
}


// to seperate original data and data to be sorted
void getData(int*& data, int* original, int size) {
	if (data) {   // if data != nullptr
		delete [] data ;
	}

	data = new int[size] ;
	for (int i = 0; i < size; i++) {
		data[i] = original[i] ;
	}
}


void selectionSort(int* data, int size) {
	for (int i = 0; i < size-1; i++) {  // i = size-1 is needless

		// find the min of the data from index = i+1 to size-1 (the last element)
		int min = i ;
		for (int j = i+1; j < size; j++) {
			if (data[j] < data[min]) {
				min = j ;
			}
		}

		swap(data[i], data[min]) ;
	}
}


void bubbleSort(int* data, int size) {
	for (int i = size-1; i > 0; i--) {
		for (int j = 1; j <= i; j++) {
			if (data[j-1] > data[j]) {
				swap(data[j], data[j-1]) ;
			}
		}
	}
}


int binarySearch(int* data, int size, int target) {
	int left = 0, right = size-1 ;

	while (left <= right) {
		int mid = left + (right - left) / 2 ;

		if (data[mid] == target) {
			return mid ;  // find the target
		}

		if (data[mid] < target) {  // left subarray
			left = mid+1 ;
		}
		else {  // right subarray
			right = mid-1 ;
        }
	}

	return -1 ;  // fail to find target
}


void quickSort(int* data, int left, int right) {
	if (left >= right) {
		return ;
	}

	int target = left, i = left+1, j = right ;  // WLOS choose the leftmost to be th pivot
	while (i < j) {
		while (i <= j && data[i] <= data[target]) { i++ ; }  // find the largest  i s.t. data[i] > data[target]
		while (i <= j && data[j] >= data[target]) { j-- ; }  // find the smallest j s.t. data[j] < data[target]
		if (i < j) { swap(data[i], data[j]) ; }
	}

	if (data[target] > data[j]) {
		swap(data[target], data[j]) ;
	}

	// recursion
	quickSort(data, left, j-1) ;
	quickSort(data, j+1, right) ;
}


void insertionSort(int* arr, int n) {
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


// for merge sort
void copyArray(int* sub, int* arr, int start, int arrSize) {
	for (int i = 0; i < arrSize; i++) {
		 sub[i] = arr[start + i] ;
	}
}


// for merge sort
void merge(int* arr, int left, int* sub1, int* sub2, int sub1Size, int sub2Size) {
	int p = left, p1 = 0, p2 = 0 ;
	while (p1 < sub1Size && p2 < sub2Size) {
		if (sub1[p1] < sub2[p2]) {
			arr[p++] = sub1[p1++] ;
		}
		else {
			arr[p++] = sub2[p2++] ;
		}
	}

	while (p1 < sub1Size) {
		arr[p++] = sub1[p1++] ;
	}
	while (p2 < sub2Size) {
		arr[p++] = sub2[p2++] ;
	}
}


void mergeSort(int* arr, int left, int right) {  // right is included
	if (left >= right) {
		return ;
	}

	// divide
	int mid = left + (right - left) / 2 ;
	mergeSort(arr, left, mid) ;
	mergeSort(arr, mid+1, right) ;

	// merge
	int sub1Size = mid - left + 1, sub2Size = right - mid ;
	int* sub1 = new int[sub1Size] ;
	int* sub2 = new int[sub2Size] ;
	copyArray(sub1, arr, left, sub1Size) ;
	copyArray(sub2, arr, mid + 1, sub2Size) ;
	merge(arr, left, sub1, sub2, sub1Size, sub2Size) ;
	delete [] sub1 ;
	delete [] sub2 ;
}


// for heap sort
void buildMaxHeap(int* arr, int root, int n) {
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


void heapSort(int* arr, int n) {
    for (int i  = (n + 1) / 2; i >= 0; i--) {  // for all internal nodes
        buildMaxHeap(arr, i, n) ;
    }

    for (int i = n-1; i > 0; i--) {
		swap(arr[i], arr[0]) ;  // so that arr[i] is the max of index = 0 to i-1
        buildMaxHeap(arr, 0, i) ;
	}
}


void printData(int* data, int size, TMemo* memo, TCheckBox* checkbox, clock_t t_begin, clock_t t_end) {
	memo->Lines->Clear() ;
	if (checkbox->Checked) {  // print data only when the "echo print" checkbox is checked
		for (int i = 0; i < size; i++) {
			memo->Lines->Add("data[" + IntToStr(i) + "] = " + IntToStr(data[i])) ;
		}
	}

	if (t_begin >= 0) {  // generate random numbers : t_begin = -1, no need to print CPU time
		float sec = (float)(t_end - t_begin) / CLOCKS_PER_SEC ;
		memo->Lines->Add("CPU time (sec.) = " + FloatToStrF(sec, ffFixed, 10, decimalPlaces));
	}
}


void checkSorted(int* data, int size, TMemo* memo, TCheckBox* checkbox) {
	if (!(checkbox->Checked)) {
		return ;  // no need to check
	}

	for (int i = 1; i < size; i++) {
		if (data[i] < data[i-1]) {
			memo->Lines->Add("Incorrectly Sorted") ;
			return ;
		}
	}

	// check sorted
	memo->Lines->Add("Correctly Sorted") ;
}


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
// button for random number generation
void __fastcall TForm1::Button1Click(TObject *Sender) {

	// clear memo of sorting and searching
	Form1->Memo2->Clear() ;
	Form1->Memo3->Clear() ;
	Form1->Memo4->Clear() ;
	Form1->Memo5->Clear() ;
	Form1->Memo7->Clear() ;
	Form1->Memo8->Clear() ;
	Form1->Memo9->Clear() ;

	try {
		// generate random n numbers within the range
		n = StrToInt(Edit1->Text) ;
		range = StrToInt(Edit2->Text) ;
		decimalPlaces = StrToInt(Edit8->Text) ;
		if (range <= 0 || n <= 0 || decimalPlaces <= 0) {
			throw new EConvertError("");
		}
		generateRandomNumbers(originalData, n, range) ;

		// output
		printData(originalData, n, Form1->Memo1, CheckBox1, -1, -1) ;
		Form1->Memo1->Lines->Add("random numbers are successfully generated.") ;
	}

	catch (const Exception& e) {
		Form1->Memo1->Lines->Clear() ; // clear the original content of the memo
		Form1->Memo1->Lines->Add("Please type positive integer n, range, and decimal places!") ;
		randomNumberGenerated = false ;
	}
}
//---------------------------------------------------------------------------
// button for selection sort
void __fastcall TForm1::Button2Click(TObject *Sender) {
	if (!checkGenerated(Form1->Memo2)) {
		return ;  // we are not allowed to sort if data is not generated
	}

	getData(data, originalData, n) ;
	clock_t t_begin, t_end ;
	t_begin = clock() ;
	selectionSort(data, n) ;
	t_end = clock() ;
	sorted = true ;

	// output
	printData(data, n, Form1->Memo2, CheckBox1, t_begin, t_end) ;
	checkSorted(data, n, Form1->Memo2, CheckBox2) ;
}
//---------------------------------------------------------------------------
// button for bubble sort
void __fastcall TForm1::Button3Click(TObject *Sender) {
	if (!checkGenerated(Form1->Memo3)) {
		return ;    // we are not allowed to sort if data is not generated
	}

	getData(data, originalData, n) ;
	clock_t t_begin, t_end ;
	t_begin = clock() ;
	bubbleSort(data, n) ;
	t_end = clock() ;
	sorted = true ;

	// output
	printData(data, n, Form1->Memo3, CheckBox1, t_begin, t_end) ;
	checkSorted(data, n, Form1->Memo3, CheckBox2) ;
}
//---------------------------------------------------------------------------
// button for binary search
void __fastcall TForm1::Button4Click(TObject *Sender) {
	try {
		Form1->Memo4->Lines->Clear() ;
		int target = StrToInt(Edit3->Text) ;
		if (!checkGenerated(Form1->Memo4)) {  // we are not allowed to perform binary search if data is not generated
			return ;
		}
		if (!sorted) {   // we are not allowed to perform binary search on not-sorted data
			Form1->Memo4->Lines->Add("Please sort the data first, so that you can perform binary search !") ;
			return ;
		}

		int success = binarySearch(data, n, target) ;
		if (success != -1) {
			Form1->Memo4->Lines->Add(IntToStr(target) + " has been found in sorted data index =" + IntToStr(success) + ".") ;
		}
		else {
			Form1->Memo4->Lines->Add(IntToStr(target) + " has not been found.") ;
		}
	}

	catch (const Exception& e) {
		Form1->Memo4->Lines->Add("Please type integer target!") ;
	}

}
//---------------------------------------------------------------------------
// button for quick sort
void __fastcall TForm1::Button5Click(TObject *Sender) {
	if (!checkGenerated(Form1->Memo5)) {
		return ;  // we are not allowed to sort if data is not generated
	}

	getData(data, originalData, n) ;
	clock_t t_begin, t_end ;
	t_begin = clock() ;
	quickSort(data, 0, n-1) ;
	t_end = clock() ;
	sorted = true ;

	// output
	printData(data, n, Form1->Memo5, CheckBox1, t_begin, t_end) ;
	checkSorted(data, n, Form1->Memo5, CheckBox2) ;
}
//---------------------------------------------------------------------------
// button for insertion sort
void __fastcall TForm1::Button7Click(TObject *Sender) {
	if (!checkGenerated(Form1->Memo7)) {
		return ;  // we are not allowed to sort if data is not generated
	}

	getData(data, originalData, n) ;
	clock_t t_begin, t_end ;
	t_begin = clock() ;
	insertionSort(data, n) ;
	t_end = clock() ;
	sorted = true ;

	// output
	printData(data, n, Form1->Memo7, CheckBox1, t_begin, t_end) ;
	checkSorted(data, n, Form1->Memo7, CheckBox2) ;
}
//---------------------------------------------------------------------------
// button for insertion sort
void __fastcall TForm1::Button8Click(TObject *Sender) {
	if (!checkGenerated(Form1->Memo8)) {
		return ;  // we are not allowed to sort if data is not generated
	}

	getData(data, originalData, n) ;
	clock_t t_begin, t_end ;
	t_begin = clock() ;
	mergeSort(data, 0, n-1) ;
	t_end = clock() ;
	sorted = true ;

	// output
	printData(data, n, Form1->Memo8, CheckBox1, t_begin, t_end) ;
	checkSorted(data, n, Form1->Memo8, CheckBox2) ;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender) {
	if (!checkGenerated(Form1->Memo9)) {
		return ;  // we are not allowed to sort if data is not generated
	}

	getData(data, originalData, n) ;
	clock_t t_begin, t_end ;
	t_begin = clock() ;
	heapSort(data, n) ;
	t_end = clock() ;
	sorted = true ;

	// output
	printData(data, n, Form1->Memo9, CheckBox1, t_begin, t_end) ;
	checkSorted(data, n, Form1->Memo9, CheckBox2) ;
}
//---------------------------------------------------------------------------
int countAlgorithm(TObject *Sender) {
	int algorithmCnt = 0;
	if (Form1->CheckBox3->Checked) algorithmCnt++;
	if (Form1->CheckBox4->Checked) algorithmCnt++;
	if (Form1->CheckBox5->Checked) algorithmCnt++;
	if (Form1->CheckBox6->Checked) algorithmCnt++;
	if (Form1->CheckBox7->Checked) algorithmCnt++;
	if (Form1->CheckBox8->Checked) algorithmCnt++;
    return algorithmCnt ;
}
// obtain CPU time and make the line chart
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	try {
		// deal with input
		n = StrToInt(Edit4->Text) ;
		range = StrToInt(Edit7->Text) ;
		step = StrToInt(Edit5->Text) ;
		repetition = StrToInt(Edit6->Text) ;
		if (n <= 0 || range <= 0 || step <= 0 || repetition <= 0) {
			throw new EConvertError("");
		}
	}

	catch (const Exception& e) {
		Form1->Memo6->Lines->Clear() ; // clear the original content of the memo
		Form1->Memo6->Lines->Add("Please type positive integer!") ;
		return ;
	}

	// create the chart
	Chart1->RemoveAllSeries();            // Remove all previous series
	Chart1->Title->Text->Clear();         // Clear chart title
	Chart1->Title->Text->Add("CPU time under different Sorting Algorithm");
	Chart1->BottomAxis->Title->Caption = "input size(n)";    // x-axis' title
	Chart1->LeftAxis->Title->Caption = "CPU time (sec.)";    // y-axis' title


	// Add the series based on selected radio button
    int algorithmCnt = countAlgorithm(Sender) ; 
	if (RadioButton1->Checked) {
    	for (int i = 0; i < algorithmCnt; i++) {
        	Chart1->AddSeries(new TLineSeries(this));
    	}
	}
	else if (RadioButton2->Checked) {
	    for (int i = 0; i < algorithmCnt; i++) {
	        Chart1->AddSeries(new TBarSeries(this));
	    }
	}
	else if (RadioButton3->Checked) {
	    for (int i = 0; i < algorithmCnt; i++) {
	        Chart1->AddSeries(new THorizBarSeries(this));
	    }
	}
	else {
	    Form1->Memo6->Lines->Add("Please select a chart!");
	    return;
	}

	// Set the title of the series based on the checkboxes
	int seriesIndex = 0;
	if (CheckBox3->Checked) Chart1->Series[seriesIndex++]->Title = "Selection Sort";
	if (CheckBox4->Checked) Chart1->Series[seriesIndex++]->Title = "Bubble Sort";
	if (CheckBox5->Checked) Chart1->Series[seriesIndex++]->Title = "Insertion Sort";
	if (CheckBox6->Checked) Chart1->Series[seriesIndex++]->Title = "Merge Sort";
	if (CheckBox7->Checked) Chart1->Series[seriesIndex++]->Title = "Quick Sort";
	if (CheckBox8->Checked) Chart1->Series[seriesIndex++]->Title = "Heap Sort";

	// clear memory of dynamic array
	if (selectionSortTime) delete [] selectionSortTime ;
	if (bubbleSortTime) delete [] bubbleSortTime ;
	if (quickSortTime) delete [] quickSortTime ;
	if (mergeSortTime) delete [] mergeSortTime ;
	if (insertionSortTime) delete [] insertionSortTime ;
	if (heapSortTime) delete [] heapSortTime ;	

	// prepare the array for storing the CPU time
	selectionSortTime = new double[repetition] ;
	bubbleSortTime = new double[repetition] ;
	quickSortTime = new double[repetition] ;
	insertionSortTime = new double[repetition] ;
	mergeSortTime = new double[repetition] ;
    heapSortTime = new double[repetition] ;

    // sort and calculate CPU time
	int current_n = n ;
	Form1->Memo6->Lines->Clear() ;
	for (int i = 0; i < repetition; i++) {  // for repetition time
		clock_t t_begin, t_end ;
		generateRandomNumbers(originalData, current_n, range) ;
        int seriesIndex = 0 ;

        // selection sort
    	if (Form1->CheckBox3->Checked) {
			getData(data, originalData, current_n) ;
			t_begin = clock() ;
			selectionSort(data, current_n) ;
			t_end = clock() ;
			Form1->Memo6->Lines->Add("n = " + IntToStr(current_n) + " selection sort") ;
			checkSorted(data, current_n, Form1->Memo6, Form1->CheckBox9) ;
			selectionSortTime[i] = static_cast<double>(t_end - t_begin) / CLOCKS_PER_SEC ;
         	Chart1->Series[seriesIndex++]->AddXY(current_n, selectionSortTime[i]);
       }

       // bubble sort		
       if (Form1->CheckBox4->Checked) {
       		getData(data, originalData, current_n) ;
			t_begin = clock() ;
			bubbleSort(data, current_n) ;
			t_end = clock() ;
			Form1->Memo6->Lines->Add("n = " + IntToStr(current_n) + " bubble sort") ;
			checkSorted(data, current_n, Form1->Memo6, Form1->CheckBox9) ;
			bubbleSortTime[i] = static_cast<double>(t_end - t_begin) / CLOCKS_PER_SEC ;
          	Chart1->Series[seriesIndex++]->AddXY(current_n, bubbleSortTime[i]);
       }
       
		// insertion sort
        if (Form1->CheckBox5->Checked) {
			getData(data, originalData, current_n) ;
			t_begin = clock() ;
			insertionSort(data, current_n) ;
			t_end = clock() ;
			Form1->Memo6->Lines->Add("n = " + IntToStr(current_n) + " insertion sort") ;
			checkSorted(data, current_n, Form1->Memo6, Form1->CheckBox9) ;
			insertionSortTime[i] = static_cast<double>(t_end - t_begin) / CLOCKS_PER_SEC ;
           	Chart1->Series[seriesIndex++]->AddXY(current_n, insertionSortTime[i]);
        }
        
		// merge sort
        if (Form1->CheckBox6->Checked) {
			getData(data, originalData, current_n) ;
			t_begin = clock() ;
			mergeSort(data, 0, current_n-1) ;
			t_end = clock() ;
			Form1->Memo6->Lines->Add("n = " + IntToStr(current_n) + " merge sort") ;
			checkSorted(data, current_n, Form1->Memo6, Form1->CheckBox9) ;
			mergeSortTime[i] = static_cast<double>(t_end - t_begin) / CLOCKS_PER_SEC ;
           	Chart1->Series[seriesIndex++]->AddXY(current_n, mergeSortTime[i]);
        }
        
		// quick sort
        if (Form1->CheckBox7->Checked) {
			getData(data, originalData, current_n) ;
			t_begin = clock() ;
			quickSort(data, 0, current_n-1) ;
			t_end = clock() ;
			Form1->Memo6->Lines->Add("n = " + IntToStr(current_n) + " quick sort") ;
			checkSorted(data, current_n, Form1->Memo6, Form1->CheckBox9) ;
			quickSortTime[i] = static_cast<double>(t_end - t_begin) / CLOCKS_PER_SEC ;
            Chart1->Series[seriesIndex++]->AddXY(current_n, quickSortTime[i]);
        }
        
		// heap sort
        if (Form1->CheckBox8->Checked) {
			getData(data, originalData, current_n) ;
			t_begin = clock() ;
			heapSort(data, current_n) ;
			t_end = clock() ;
			Form1->Memo6->Lines->Add("n = " + IntToStr(current_n) + " heap sort") ;
			checkSorted(data, current_n, Form1->Memo6, Form1->CheckBox9) ;
			heapSortTime[i] = static_cast<double>(t_end - t_begin) / CLOCKS_PER_SEC ;
           	Chart1->Series[seriesIndex++]->AddXY(current_n, heapSortTime[i]);
        }
        
		current_n += step ;
	}

   	// width of the line
	for (int i = 0; i < algorithmCnt; i++) {
		Chart1->Series[i]->Pen->Width = 3;
	}
}
//---------------------------------------------------------------------------
