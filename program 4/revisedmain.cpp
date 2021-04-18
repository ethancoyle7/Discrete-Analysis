////////////////////////////////////////////////////
//   Author:       Ethan Coyle                    //
//   Class:        Discrete Data Structures       //
//   Professor:    Dr.StringFellow                //
//   Program 4:    Algorithm Timing Comparisons   //
//   Due Date:     April 23,2021                  //
////////////////////////////////////////////////////
////////////////////////////////////////////////////
//                                                //
// The overview of this program is that we are    //
// goint to be perfomring recursive and iterative //
// searches on an array of alloted values and then//
// calculating the time complexity that it takes  //
// to perform each search and display to the view //
// of the user in a nice easy to read format in an//
//output file                                     //
////////////////////////////////////////////////////


#include <iostream> // user input/output
#include <fstream> // file streaming
#include <iomanip>   //for output manipulation
#include <stdlib.h> //srand, rand
#include <chrono>    //for the start and stop time
#include <time.h>    //clock, clock_t
#include<cmath> // perfomring the log math

using namespace std;
//const int MAXSIZES = 5;

//function prototypes for the file and heading print
void openFiles(ofstream& OutFile);
void printPageHeading(ofstream& OutFile,int x);
void printColumnHeadings(ofstream& OutFile);

//function prototypes for the rand number sorting
long long iBinSearch(int Array[], long long,
	long long , long long );
long long rBinSearch(int Array[], long long,
	long long , long long );
void IMergeSort(int Array[], long long );
void RMergeSort(int Array[], long long, long long);
void Merge(int*, long long, long long, long long);
void TimeComplexity(ofstream& OutFile, long long);

//function prototype to create values and check time
int* GenerateValues(int);
int* copyValues(int* Array, int n);

//the different sizes of the time complexity as a glob const
const int sizes[] = { 100,1000,10000,100000,1000000 };

//set to 32 bit instead of standard 64
//int main gives alot of problems because preset int64_t main so change 
//it to int32-t got problem running while running program

int main()
{
	//int sizes[MAXSIZES] = { 100, 1000, 10000, 100000, 1000000 };
	srand(time(NULL)); //set time to null

	ofstream OutFile;
	openFiles(OutFile);// prompt for input output

	//for each iteration of the ouput(i.e 5
	//print out the header and the string output

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

//now we will generate out rand numbers
///////////////////////////////////////////////////////
//function name =                                    //
// -int* GenerateValues(int n)                       //
//                                                   //
// parameters                                        //
// - takes in integer parameters                     //
//                                                   //
//what does it do?                                   //
//	- the purpose of this is to create a dynamically //
//	- allocated array full of random numbers to      //
//	- compute the time complexity                    //
//return value                                       //
//                                                   //
//	- this functin return the array of rand nums     //
///////////////////////////////////////////////////////

int* GenerateValues(int n) 
{
	int* Array = new int[n];
	for (int i = 0;i < n;i++) 
	{
		Array[i] = rand();
	}
	return Array;
}
///////////////////////////////////////////////////////
//function name =                                    //
// -int* copyValues(int* Array, int n)               //
//                                                   //
// parameters                                        //
// - takes in integer and pointer to int array       //
//                                                   //
//what does it do?                                   //
//	- the purpose of this funct. is                  //
//  - copy the values over into a new array          //
//  - not really necessary but copy the array to do  //
//   recursive
//return value                                       //
//                                                   //
//	- this functin return copy array of rand nums    //
///////////////////////////////////////////////////////
int* copyValues(int* Array, int n)
{
	int* copyarr = new int[n];
	for (int i = 0;i < n;i++) 
	{
		copyarr[i] = Array[i];
	}
	return copyarr;
}

///////////////////////////////////////////////////////
//function name =                                    //
// -void TimeComplexity(ofstream& OutFile,           //
//  long long p)                                     //
//                                                   //
// parameters                                        //
// - takes the outfile streaming and the rand num    //
// -  and uses this number to compute time complex   //
//                                                   //
//what does it do?                                   //
//	- the purpose of this is to take in the long     //
//  - long number and compute time complexity        //
//return value                                       //
//                                                   //
//	- this function doesnt return anything (void)    //
// - however it will be called and passes the print  //
// - value of computed time back to main             //
///////////////////////////////////////////////////////
void TimeComplexity(ofstream& OutFile, long long p)
{
	long long TimeResult[7] = {};//how many outputs 7
	//initialize n for computation using const int sizes
	long long  n = sizes[p];
	long long nlogn = (long long)((double)n * log2(n));
	TimeResult[0] = n;
	TimeResult[1] = nlogn;
	TimeResult[4] = n * n;

	using Clock = chrono::high_resolution_clock;
	//variables for timings
	clock_t start, stop;

	int* Array = GenerateValues(n);
	int* CopiedArray = copyValues(Array, n);
	//time code
	//get start

	//below start to stop then assgin time to each

	start = Clock::now().time_since_epoch().count();
	IMergeSort(Array, n);
	stop = Clock::now().time_since_epoch().count();
	//assign the time to this
	TimeResult[5] = (double)(stop - start);


	start = Clock::now().time_since_epoch().count();
	RMergeSort(CopiedArray, 0, n - 1);
	stop = Clock::now().time_since_epoch().count();
		//result of time is 6th collum
		TimeResult[6] = (double)(stop - start);

	start = Clock::now().time_since_epoch().count();
	iBinSearch(Array, 0, n - 1, Array[rand() % n]);
	stop = Clock::now().time_since_epoch().count();
	//result is the time complexity of 3rd collumn
	TimeResult[3] = (double)(stop - start);

	start = Clock::now().time_since_epoch().count();
	rBinSearch(Array, 0, n - 1, Array[rand() % n]);
	stop = Clock::now().time_since_epoch().count();
	//result goes in 2nd collum
		TimeResult[2] = (double)(stop - start);

	for (int i = 0; i < 7; i++)
	{
		//output the results
		OutFile << setprecision(0)<< setw(15) << TimeResult[i];
	}
	OutFile << '\n';
	//destroy both arrays
	delete[] Array;
	delete[] CopiedArray;
}


/////////////////////////////////////////////////////
// function name                                   //
// -void printPageHeading(ofstream& OutFile, int x)//
//                                                 //
// parameters-                                     //
// -streaming to the outfile and iterative throuthg//
// -the five iterations                            //
//                                                 //
// what it does-                                   //
// -the purpose of this function is to print       //
// -the header for output                          //
//                                                 //
// return type-null(doesnt return value just prints//
/////////////////////////////////////////////////////

//print page and column headings
void printPageHeading(ofstream& OutFile, int x)
{
	//prepare the outfile for page heading formatting
	OutFile << "Ethan Coyle" << '\n';
	OutFile << "Program 4 Algorithm"<<
		" Timing Comparisons" << "\n\n";
	//iterate through all 5 cases
	OutFile << "Time Complexity " << x <<
		": " <<'\n';
}
/////////////////////////////////////////////////////
// function name                                   //
// -void printColumnHeadings(ofstream& OutFile)    //
//                                                 //
// parameters-                                     //
// -streaming to the outfile                       //
//                                                 //
// what it does-                                   //
// -the purpose of this function is to print       //
// -string heading to output file for each time    //
// -complexity                                     //
//                                                 //
// return type-null(doesnt return value just prints//
/////////////////////////////////////////////////////

//print  column headings
void printColumnHeadings(ofstream& OutFile)
{
	//string output
	string s[] = { "n","nlogn" , "iBin" ,
		"rBin" , "n^2" ,"iMerge" , "rMerge" };

	//for all of the time complexities
	for (int i = 0; i < 7; i++)
	{
		OutFile << setw(15) << s[i];
	}
	OutFile << '\n';
	OutFile << "------------------------------------"<<
		"-------------------------------------------"<<
		"--------------------------\n";
}

////////////////////////////////////////////////////////////
//function name-                                          //
//-long long iBinSearch(int Array[], long long l,         //
//  long long r, long long x)                             //
//                                                        //
//parameters-                                             //
//- acceots the pointer to array,left,right and the number//
//                                                        //
// what it does-                                          //
//- the purpose of this function                          //
//-is to perform a iterative  binary search on the array  //
//                                                        //
// return type-                                           //
// -this function returns the recursive middle value of   //
//     array  if present                                  //
////////////////////////////////////////////////////////////
//Perform iterative binary search for the key in the array
long long iBinSearch(int Array[], long long l, 
	long long r, long long x)
{
	while (l <= r) 
	{
		long long m = l + (r - l) / 2;

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

	// retun -1 if not present
	return -1;
}

////////////////////////////////////////////////////////////
//function name-                                          //
//-long long rBinSearch(int Array[], long long l,         //
//  long long r, long long x)                             //
//                                                        //
//parameters-                                             //
//- acceots the pointer to array,left,right and the number//
//                                                        //
// what it does-                                          //
//- the purpose of this function                          //
//-is to perform a recursive binary search on the array   //
//                                                        //
// return type-                                           //
// -this function returns the recursive middle value of   //
//     array                                              //
////////////////////////////////////////////////////////////

//Perform recursive binary search for specified value in array
long long rBinSearch(int Array[], long long l, 
	long long r, long long x)
{
	if (r >= l) 
	{
		long long Middle = l + (r - l) / 2;

		// If the element is present at the middle
		// return value
		if (Array[Middle] == x)
			return Middle;

		// If element is smaller than mid, can only
		//be in left sub array
		if (Array[Middle] > x)
			return rBinSearch(Array, l, Middle - 1, x);

		// Else it is in the right subarray
		return rBinSearch(Array, Middle + 1, r, x);
	}

	//if the value not in array return -1
	return -1;
}

////////////////////////////////////////////////////////////
//function name-                                          //
//-void Merge(int* x, long long left, long long m,        //
//  long long  right)                                     //
//                                                        //
//parameters-                                             //
//- accepts the pointer to array val. left rihgt and      //
//  middle  using long long for computation               //
//                                                        //
// what it does-                                          //
//- the purpose of this function is to perform a          //
//  merge sort on the alotted array using left,middle     //
// and right to sort the array and Merge two sorted       //
// halves of an array                                     //
//                                                        //
//this returns nothing because it is void                 //
////////////////////////////////////////////////////////////

//now for merge sorts

void Merge(int* x, long long left, long long m,
	long long  right)
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
////////////////////////////////////////////////////////////
//function name-                                          //
//-void IMergeSort(int Array[], long long n)              //
//                                                        //
//parameters-                                             //
//- acceots the array or random long long number          //
//                                                        //
// what it does-                                          //
//- the purpose of this function is to                    //
// - perfrom a mergesort inductvely by reading the current//
// -size of the array and then merge the middle right and //
// left of the sorted array                               //
//                                                        //
//this returns nothing because it is void                 //
////////////////////////////////////////////////////////////
void IMergeSort(int Array[], long long n)
{
	long long CurrentSize;//current size to merge
	long long Left; //leftsub array to merge

	for (CurrentSize = 1; CurrentSize <= n - 1; CurrentSize = 
		2 * CurrentSize)
	{
		// choose start pt. of different sub array
		//of current size
		for (Left = 0; Left < n - 1; Left += 2 * CurrentSize)
		{
			//fin the end point of left sub array
			int Middle = min(Left + CurrentSize - 1, n - 1);

			int Right = min(Left + 2 * CurrentSize - 1, n - 1);

			// Merge Subarrays Array[Left...Middle] & Array
			//[Middle+1...Right]
			Merge(Array, Left, Middle, Right);
		}
	}
}

////////////////////////////////////////////////////////////
//function name-                                          //
//-void RMergeSort(int Array[], long long l, long long r) //
//                                                        //
//parameters-                                             //
//- acceots the array or random long long numbers,        //
//       left and right values                            //
//                                                        //
// what it does-                                          //
//- the purpose of this function is to perform a          //
//  recursive merge sort  and call the function           //
//  merge to access the array                             //
//                                                        //
//this returns nothing because it is void                 //
////////////////////////////////////////////////////////////

void RMergeSort(int Array[], long long l, long long r)
{
	
	if (l < r)
	{
		//perform the recursive merge sorts
		long long m = l + (r - l) / 2;
		RMergeSort(Array, l, m);
		RMergeSort(Array, m + 1, r);
		Merge(Array, l, m, r);
	}
}
