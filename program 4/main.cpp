#include <iostream> // user input/output
#include <fstream> // file streaming
#include <iomanip>   //for output manipulation
#include <stdlib.h> //srand, rand
#include <chrono>
#include <time.h>    //clock, clock_t
#include <cassert>
#include<cmath>


using namespace std;

//function prototypes for the file and heading print
void openFiles(ofstream& OutFile);
void printPageHeading(ofstream& OutFile,int x);
void printColumnHeadings(ofstream& OutFile);

//function prototypes for the rand number sorting
long long iBinSearch(int Array[], long long, long long , long long );
long long rBinSearch(int Array[], long long, long long , long long );
void IMergeSort(int Array[], long long );
void RMergeSort(int Array[], long long, long long);
//void Merge(int* x, long left, long m, long right);
void Merge(int, long long, long long, long long);
void TimeComplexity(ofstream& OutFile, long long);

//function prototype to create values and check time
int* GenerateValues(int);
int* copyValues(int* Array, int n);

//the different sizes of the time complexity

int sizes[] = { 100,1000,10000,100000,1000000 };

int main()
{
	srand(time(NULL));

	ofstream OutFile;
	openFiles(OutFile);// prompt for input output

	for (int p = 0;p < 5; p++)
	{
		//creating instances of each on one output
		printPageHeading(OutFile, p + 1);
		printColumnHeadings(OutFile);

		//print out five times
		for (long long j = 0;j < 5;j++)
		{
			TimeComplexity(OutFile, j);
		}
		OutFile << "\n\n\n";
	}

	OutFile.close();//close the outfile
	return 0;
}

//#####################################################//
//f(x) name                                            // 
//  void openFiles( ofstream& OutFile)                 //
//                                                     //
//what it does?                                        //
// -> purpose is to user input in and outfile          //
//                                                     //
//paramters                                            //
// -> utilizes the ofstream and outfile                //
//                                                     //
// return type                                         //
// -> no return type because  void                     //
//#####################################################//

void openFiles(ofstream& OutFile)
{
	// Declare variable for the Files. 
	char outFileName[40];


	// Prompt the user for OutFile name
	cout << "Enter the output file name: ";
	cin >> outFileName;

	// Open outfile.
	OutFile.open(outFileName);
}





int* GenerateValues(int n) 
{
	int* Array = new int[n];
	for (int i = 0;i < n;i++) 
	{
		Array[i] = rand();
	}
	return Array;
}

int* copyValues(int* Array, int n)
{
	int* copyarr = new int[n];
	for (int i = 0;i < n;i++) 
	{
		copyarr[i] = Array[i];
	}
	return copyarr;
}


void TimeComplexity(ofstream& OutFile, long long p)
{
	long long TimeResult[7];
	long long  n = sizes[p];
	long long nlogn = (long long)((double)n * log2(n));
	TimeResult[0] = n;
	TimeResult[1] = nlogn;
	TimeResult[4] = n * n;
	int* Array = GenerateValues(n);
	int* CopiedArray = copyValues(Array, n);

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	IMergeSort(Array, n);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	TimeResult[5] = chrono::duration_cast<chrono::nanoseconds>
		(end - begin).count();


	begin = chrono::steady_clock::now();
	RMergeSort(CopiedArray, 0, n - 1);
	end = chrono::steady_clock::now();
	TimeResult[6] = chrono::duration_cast<chrono::nanoseconds>
		(end - begin).count();


	begin = chrono::steady_clock::now();
	iBinSearch(Array, 0, n - 1, Array[rand() % n]);
	end = chrono::steady_clock::now();
	TimeResult[3] = chrono::duration_cast<chrono::nanoseconds>
		(end - begin).count();


	begin = chrono::steady_clock::now();
	rBinSearch(Array, 0, n - 1, Array[rand() % n]);
	end = chrono::steady_clock::now();
	TimeResult[2] = chrono::duration_cast<chrono::nanoseconds>
		(end - begin).count();

	for (int i = 1; i < n; i++) 
	{
		assert(Array[i] >= Array[i - 1]);
		assert(CopiedArray[i] >= CopiedArray[i - 1]);
	}
	for (long long i = 0; i < 7; i++)
	{
		OutFile << setw(15) << TimeResult[i];
	}
	OutFile << '\n';
	//destroy both arrays
	delete[] Array;
	delete[] CopiedArray;
}

//print page and column headings
void printPageHeading(ofstream& OutFile, int x)
{
	OutFile << " Ethan Coyle" << '\n';
	OutFile << " Program 4 Algorithm Timing Comparisons" << '\n';
	//iterate through all of the tests
	OutFile << "Time Complexity " << x << ": " << '\n';
}

//print  column headings
void printColumnHeadings(ofstream& OutFile)
{
	string s[] = { "n","nlogn" , "iBin" , "rBin" , "n^2" ,
		"iMerge" , "rMerge" };
	for (int i = 0; i < 7; i++)
	{
		OutFile << setw(15) << s[i];
	}
	OutFile << '\n';
	OutFile << "             ----------------------------------------" <<
		"----------------------------------------------------------\n";
}

//Perform iterative binary search for the key in the array
long long iBinSearch(int Array[], long long l, long long r, long long x)
{
	while (l <= r) 
	{
		int m = l + (r - l) / 2;

		// Check if x is present at Middle
		if (Array[m] == x)
			return m;

		// If x greater, ignore left half
		if (Array[m] < x)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	// if we reach here, then element was
	// not present
	return -1;
}

//Perform recursive binary search for the key in the array
long long rBinSearch(int Array[], long long l, long long r, long long x)
{
	if (r >= l) 
	{
		long long Middle = l + (r - l) / 2;

		// If the element is present at the middle
		// itself
		if (Array[Middle] == x)
			return Middle;

		// If element is smaller than Middle, then
		// it can only be present in left subarray
		if (Array[Middle] > x)
			return rBinSearch(Array, l, Middle - 1, x);

		// Else the element can only be present
		// in right subarray
		return rBinSearch(Array, Middle + 1, r, x);
	}

	// We reach here when element is not
	// present in array
	return -1;
}




//now for merge sorts
// 
//Merge two sorted halves of an array
void Merge(int* x, long long left, long long m, long long  right)
{
	//determine sizes of two sorted parts
	long long  n1 = m - left + 1;
	long long n2 = right - m;

	// Dynamically allocate temp arrays for both subarrays
	int* Left = new int[n1];
	int* Right = new int[n2];

	//Copy data to temp arrays Left[] and Right[]
	for (long i = 0; i < n1; i++)
		Left[i] = x[left + i];
	for (long j = 0; j < n2; j++)
		Right[j] = x[m + 1 + j];

	// Merge the temp arrays back into Array[l..r]


	long i = 0;		// Initial index of first subarray
	long j = 0;		// Initial index of second subarray
	long k = left;	// Initial index of merged subarray


	//while elements in both subarrays, merge
	while (i < n1 && j < n2) {
		if (Left[i] <= Right[j]) {
			x[k] = Left[i];
			i++;
		}
		else {
			x[k] = Right[j];
			j++;
		}
		k++;
	}

	// Copy remaining elements of Left[], if there are any
	while (i < n1) {
		x[k] = Left[i];
		i++;
		k++;
	}

	// Copy remaining elements of Right[], if there are any
	while (j < n2)
	{
		x[k] = Right[j];
		j++;
		k++;
	}

	delete[] Left;
	delete[] Right;
}

void IMergeSort(int Array[], long long n)
{
	long long CurrentSize;//current size to merge
	long long Left; //leftsub array to merge

	for (CurrentSize = 1; CurrentSize <= n - 1; CurrentSize = 2 * CurrentSize)
	{
		// Pick starting point of different subarrays of current size
		for (Left = 0; Left < n - 1; Left += 2 * CurrentSize)
		{
			// Find ending point of left subarray. Middle+1 is starting
			// point of right
			int Middle = min(Left + CurrentSize - 1, n - 1);

			int Right = min(Left + 2 * CurrentSize - 1, n - 1);

			// Merge Subarrays Array[Left...Middle] & Array[Middle+1...Right]
			Merge(Array, Left, Middle, Right);
		}
	}
}

void RMergeSort(int Array[], long long l, long long r)
{
	if (l < r)
	{

		// Same as (l+r)/2 but avoids
		// overflow for large l & h
		long long m = l + (r - l) / 2;
		RMergeSort(Array, l, m);
		RMergeSort(Array, m + 1, r);
		Merge(Array, l, m, r);
	}
}
