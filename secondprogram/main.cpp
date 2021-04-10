//****************************************************************//
//                   Ethan Coyle                                  //
//                   Dr.StringFellow                              //
//                   CMPS 2433 Discrete Structures and Analysis   //
//                   Program 2                                    //
//                                                                //
// The prupose of this program is to utilizes arithmetic          //
// sequences within 4 function to calulate the various outputs of //
// g(x),f(x), f and g inverse and utilize the print header funct. //
// to display in an easy to read format for the viewer.           //
//                                                                //
//****************************************************************//

#include <iostream>
#include <fstream>
#include<iomanip>// for output formatting
using namespace std;

// Funtion Prototype to Asked the user for name of files to be use.
void openFiles(ifstream& InFile, ofstream& OutFile);

//function prototype to calculate f(x)
double f(double);

// function prototype to calculate g(x)
double g(double);

//function prototype to calculate g inverse
double gInv(double);

//function prototype to calculate f inverse
double fInv(double);

//function protype to print out headings
void printheading(ofstream& outfile);



int main()
{
	ifstream InFile;
	ofstream OutFile;
	openFiles(InFile, OutFile);// go to function to prompt for input output

	printheading(OutFile);//print heading

	while (!InFile.eof())//while not the end of file
	{
		double x;
		while (InFile >> x)// while the infile is still a number
		{
			//read x
		//calculate the given values for x
			OutFile << setprecision(2) << fixed << setw(5) << x <<
				setw(10) << f(x) << setw(10) << g(x) << setw(10) <<
				fInv(x) << setw(10) << gInv(x) << setw(10) <<f(g(x)) << 
				setw(10) << g(f(x)) << setw(10) << fInv(f(x)) <<
				setw(10) << gInv(g(x)) << '\n';
		}
	}

	InFile.close();   // close InFile
	OutFile.close();  // close outfile

	return 0;
};

//*************************************************************//
//Function name -> double f(double x)                          //
//                                                             //
//what it does?                                                //
// -> this function will take the input of x as aa double      //
// -> and store the result of 3* x+5 and store it then pass    //
//  ->back to main  or the computatio 4*x+1 with my last name  //
//                                                             //
//paramters                                                    //
// -> passes in a single double integer for computation        //
//                                                             //
// return type                                                 //
// -> returns a single double integer for x                    //
/////////////////////////////////////////////////////////////////
double f(double x)
{
	double result;
	
	result = 3 * x + 5;
	//result = 4 * x + 1;// for the second output with last name coyle
	return result;
}

//*************************************************************//
//Function name -> double g(double x)                          //
//                                                             //
//what it does?                                                //
// -> this function will take the input of x as aa double      //
// -> and store the result ((3 * x) / 5 + 1)and store it       //
//  -> then pass it back to main or perform x-1 for lastnamer  //
//   -> coyle                                                  //
//  ->back to main  or the computatio 4*x+1 with my last name  //
//                                                             //
//paramters                                                    //
// -> passes in a single double integer for computation        //
//                                                             //
// return type                                                 //
// -> returns a single double integer for x                    //
/////////////////////////////////////////////////////////////////

//g(x)
double g(double x)
{
	double result;
	//result = x - 1; //for second output with last name coyle
	result = ((3 * x) / 5 + 1);

	return  result;
}

//*************************************************************//
//Function name -> double fInv(double y)                       //
//                                                             //
//what it does?                                                //
// -> this function will take the input of x as aa double      //
// -> and store the result of ((y - 5) / 3);and store it       //
//  ->back to main  or the computatio 4*x+1 with my last name  //
//                                                             //
//paramters                                                    //
// -> passes in a single double integer for computation        //
//                                                             //
// return type                                                 //
// -> returns a single double integer for x                    //
/////////////////////////////////////////////////////////////////

//fInv(y)
double fInv(double y)
{

	double F_inverse;
	F_inverse = ((y - 5) / 3);

	return F_inverse;
}

//*************************************************************//
//Function name -> double gInv(double y)                       //
//                                                             //
//what it does?                                                //
// -> this function will take the input of x as aa double      //
// -> and store the result of ((5 * y - 5) / 3);and store it   //
//  ->back to main  or the computatio 4*x+1 with my last name  //
//                                                             //
//paramters                                                    //
// -> passes in a single double integer for computation        //
//                                                             //
// return type                                                 //
// -> returns a single double integer for x                    //
/////////////////////////////////////////////////////////////////

//ginv(y)
double gInv(double y)
{
	double G_Inverse;

	G_Inverse = ((5 * y - 5) / 3);

	return G_Inverse;
}

//*************************************************************//
//Function name -> void printheading(ofstream& OutFile)       //
//                                                             //
//what it does?                                                //
// -> this functions purpose is to just formate the header     //
// -> for the output                                           //
//                                                             //
//paramters                                                    //
// -> utilizes the ofstream and outfile                        //
//                                                             //
// return type                                                 //
// -> no return type because it is void print functon          //
/////////////////////////////////////////////////////////////////

//function to print heading
void printheading(ofstream& OutFile)
{
	OutFile << " Ethan Coyle " << '\n';
	OutFile << " Program 2: Function Composition" << '\n';
	//set up header in the output to display the header
	OutFile << '\n' << setw(5) << "  x" << setw(10) << "  f(x)" << setw(10) <<
		"  g(x)" << setw(10) << "  fInv(x)" << setw(10) << "  gInv(x)" <<
		setw(10) << "  f(g(x))" << setw(10) << "  g(f(x))" << setw(10) <<
		"  fInv(f(x))" << setw(10) << "  gInv(g(x))" << '\n';
	
	for (int i = 0; i < 90; i++)// create a divider using dashes
		OutFile << "-"; OutFile << '\n';
}


//**********************************************************************//
 //* Function Name:												        //
 //*	->void openFiles(ifstream& InFile, ofstream& OutFile)		    //
 //*    -> prototype at the top                                         //
 //																	    //
 //* What does it do?													//
//	  -> the purpose of this function is to have user inputted infile   //
 //   -> then stream from that input file as well as a user inputted    //
//	  -> outfile for OutFile destination								//
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
