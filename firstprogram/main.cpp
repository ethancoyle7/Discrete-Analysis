//*************************************************************************//
//                   Name:        Ethan Coyle                              //
//					 Class:       Discrete Structures and Analysis		   //
//					 Instructor:  Dr. StringFellow		    		       //
//					 Program 1:   Computing GreyCode	     		       //
//*************************************************************************//
//*************************************************************************//
//																		   //
// The purpose of this program is to read a user inputted data file		   //
// and peruse through either case number A or casenumber B.				   //
// After reading in a case A, the program will go to the function		   //
// computeint function to shift the bits over one to the right,			   //
// then perform a exclusive or on it and then it will return that computed //
// Value back to main to be printed out. If the case number is a B, it     //
// go to the function int ComputeGrayPosition(int) to compare the bits and // 
// add those all together to a decimal value number and then return to     //
//main with that computed value.										   //
//************************************************************************ //
#include<cmath>// for pow function
#include <iostream>
#include <fstream>

using namespace std;


// Funtion Prototype to Asked the user for name of files to be use.
void openFiles(ifstream& InFile, ofstream& OutFile);

// function prototype to compute grey bit conversion
//to do the right shift by one and exclusive or computation
int ComputeGrayInt(int, int);

// function prototype to calculate
int computegraypostion(int);


int main()
{
	//unsigned int means that non negative numbers always positive
	unsigned int n, k, g;
	int  CaseNumbers;
	char Letter;


	ifstream InFile;
	ofstream OutFile;
	openFiles(InFile, OutFile);

	//print out header to the outfile
	OutFile << "\t\t _________________________________________________\n";
	OutFile << "\t\t |   Author:   Ethan Coyle                       |\n";
	OutFile << "\t\t |   Program1: Bitwise &  Grey Code Computation  |\n";
	OutFile << "\t\t |   CMPS 2443 202, Dr. Stringfellow             |\n";
	OutFile << "\t\t |   Semester: Spring 2021                       |\n";

	// first line of the code will be the ammount  of inputs
	// cases value.e. 18, 25, 9000,1,000,000,000

	while (InFile >> CaseNumbers)//read in the first line which is the 
								 // case number ammounts  go to next line
	{
		OutFile << "\t\t |   There are: " << CaseNumbers
			<< "  cases " << "                       |\n";
		OutFile << "\t\t |_______________________________________________|" <<
			"\n\n";

		while (!InFile.eof())// while not the end of the file
		{
			// input A or B as characer and check
			InFile >> Letter;

			if (Letter == 'A')   // if A, read 2 values
			{
				InFile >> n >> k;
				// go to the calling function for computation then output
				OutFile << ComputeGrayInt(n, k) << '\n';
			}
			else // if B, read 1 decimal value for conversion
			{
				InFile >> g;// read in the decimal of b

				OutFile << computegraypostion(g) << '\n';
			}
		}
	}
	InFile.close();   // close InFile
	OutFile.close();  // close outfile
	//system("pause");
	return 0;
}


//**********************************************************************//
 //* Function Name:												        //
 //*	->void openFiles(ifstream& InFile, ofstream& OutFile)		    //
 //*    -> prototype at the top                                         //
 //																	    //
 //* What does it do?													//
//	  -> the purpose of this function is to have user inputted infile   //
 //   -> then stream from that input file as well as a user inputted    //
//	  -> outfile for cout destination									//
//						    	  	                                    //
 //* Parameters:	    						                       	//
 //*  ->   ifstream&  Array for letters for file name max 40 chars.     //
 //*  ->  ofstream&   Array for letters for file name max 40 chars.     //
 //*																    //
 //* Returns:														    //
 //*   -> Void( the variables are being passed by reference so no return//   
 //*********************************************************************//

void openFiles(ifstream& InFile, ofstream& OutFile)
{
	// Declare variable for the Files. 
	char inFileName[40];
	char outFileName[40];

	// Prompt the user for InFile name
	cout << "Enter the input file name: ";
	cin >> inFileName;

	// open input file
	InFile.open(inFileName);

	// Prompt the user for OutFile name
	cout << "Enter the output file name: ";
	cin >> outFileName;

	// Open outfile.
	OutFile.open(outFileName);
}

//******************************************************************//
// Function Name                                                    //
//    ->int ComputeGrayInt(int n, int k)    				        //    
// What does it do?													//
//	  -> The purpose of this fuction is to read in value n and k	//
//    -> and then it will compute k by shifting the bit to right one//
//	  -> and then perfrom an exclusive or on this and then putting  //
//	  -> into the int result to return the computation				//
// Parameters:	    												//
//  -> two integers n and k first and second value      			//
//																	//
// Returns:															//
//  -> this function returns an integer of type result which is     //
//	-> the computed ammount stored in result						//
//******************************************************************//

int ComputeGrayInt(int n, int k)
{
	int Result;
	// this reads the number n in and computes the bit k and shifts it to
	//the right 1 bit and the does the exclusive or with the computed bu=it
	// and then returns the result
	
	Result = k ^ (k >> 1);// ^ is the exclusive or (chift to right 1 do XOR)

	//return the computed result
	return  Result;
}


//*************************************************************//
// Function Name:`											   //
//   ->  int ComputeGrayPosition(int  g)					   //
// What does it do?										       //
//	  -> the purpose of this function is to read in a input    //
//    ->  of g which is a decimal value, do a conversion with  //
//     -> XOR and convert the computation back to decimal from //
//     -> binary                                               //
// Parameters:	    									       //
//  -> the parameter for this function are reading in the      //
//	->decimal value as int to do the conversion				 n //
// Returns:													   //
//  -> this returns the integer value for the converted decimal//
//*************************************************************//

int computegraypostion(int g)
{
	// will not be negative values
	unsigned int DecimalValue = 0;
	unsigned int value = 0; // each value holder for binary
	unsigned int RemainingValues;


	if (g % 10 > 1)// as long as remainder  is greater than 1
	{
		return g ^ (g >> 1); // returns the decimal converted value
	}
	else // any other case
	{
		while (g != 0)// while g is not equal to 0 // conversion 
			// 
		{
			RemainingValues = g % 10; //find the remainder base 10
			//  take the RemainingValues of the binary code and 
			
			//store it into RemainingValues
			g /= 10;
			
			//cout << g;
			//system("pause");
			
			
							//protect loss of data potentially so (int)
			 DecimalValue += int(RemainingValues * pow(2, value));// 
			// use the pow function to do add the powers of 2 the the place
			// accumulate and store in decimalvalue from binary
			
			//cout << DecimalValue;
			//system("pause");
			
			++value;
		}
		return DecimalValue ^ (DecimalValue >> 1); 
		// returns the decimal converted value after 
	}   // shift right 1 do xor return result

	return 0;// exit out of function
}
// shift the bits to right then exclusive or the bits
// convert the decimal value to binary, shift the bits one to 
//right then perform XOR return the integer value for g after
// conversion




