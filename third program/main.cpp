//##############################################//
//   Author- Ethan J Coyle                      //
//   Program- Program 3- Computing GCD and LCM  //
//   Professor- Dr. StringFellow                //
//   Class- Discrete Anaylsis                   //
//                                              //
// The purpose of this program is to read in    //
// an infile of strings of numbers and then     //
// compute the corresponding gcd and lcm        //
// and then return to the output file to maxGCD //
// and the minimum LCM in a nice, easy to read  //
// format for the viewer                        //
//##############################################//

#include <iostream>
#include <fstream>//in and outfile streaming
#include <iomanip>// for formating output
#include <sstream>// for string reading

using namespace std;

// function prototypes for calculations

int Calculate_GCD(int, int);
int Calculate_LCM(int, int);
int InputData(ifstream& InFile, int[]);
void MaxGCDandMinLCM(int*, int, int&, int&);

//protypes for capturing infile and printing out header
void Header(ofstream& OutFile);
void openFiles(ifstream& InFile, ofstream& OutFile);


int main()
{

    // open input file
    ifstream InFile;
    ofstream OutFile;
    openFiles(InFile, OutFile);// prompt for input output

    int MaxGCD, MinimumLCM, CaseNumbers, length;
    // initialize the casenumber counter, length of the 
    //input string, values for min and max gcd and lcm

    int list[100]; // array to store ints set 10 100

    Header(OutFile);//print header to outpur

    // read the number of test cases from file
    InFile >> CaseNumbers;

    //print to the output file
    OutFile << "There are : " << CaseNumbers << " Cases. " <<
        "\n\n";

    while (!InFile.eof())
    {//until eof() is encountered

        // output table header
        OutFile << right << setw(10) << "MaxGCD" << right <<
            setw(10) << "MinLCM" << endl;
        //start loop to loop through all the lines while still
        //infile
        for (int i = 0;i < CaseNumbers;i++)
        {
            length = InputData(InFile, list); // read the list and
                                 //return the length of read list
            //call the gcd and lcm function to calculate
            MaxGCDandMinLCM(list, length, MinimumLCM, MaxGCD);
            //returning the values of make and min pointer inside
            // determine the maximum GCD and minimum LCM of the list

            //print out the result of calculation
            OutFile << right << setw(10) << MaxGCD << right <<
                setw(10) << MinimumLCM << endl;
        }
    }

    // close the files
    InFile.close();
    OutFile.close();

    return 0;//end program
}
// end of program
//#####################################################//
//f(x) name                                            // 
//  void openFiles(ifstream& InFile, ofstream& OutFile)//
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

//#########################################//
//f(x) name                                // 
//  -> void printheading(ofstream& OutFile)//
// -> void Header(ofstream& OutFile, int   //
//          MaxGCD, int MinimumLCM)        //
//what it does?                            //
// -> purpose is to just formate the header//
// -> for the output                       //
//                                         //
//paramters                                //
// -> utilizes the ofstream and outfile    //
//                                         //
// return type                             //
// -> no return type because  void         //
//#########################################//
// function to output the MaxGCD and MinimumLCM to file
void Header(ofstream& OutFile)
{
    OutFile << "Ethan Coyle " << '\n';
    OutFile << "Program 3 Computing GCD and LCM "
        << "\n\n";

}

//###########################################//
// function name
//  ->int InputData(ifstream& InFile, int list[])
//
//parameters
//  -> accets the infile that is opened in the infile
//  -> search function, and accepts the integer array
//  -> list that is set to max 100
//
//what it does
//-> the purpose of this function is to read from the infile
//-> and read the string of integers on each line and store it 
//-> in an array that makes it easier to compute the GCD and LCM
//
//return type
//-> returns the integer size of each individual line to be used in
//-> computational processing in the other functions
//################################################################//

int InputData(ifstream& InFile, int list[])
{
    string line;
    getline(InFile, line); // read a line from file
    if (line == "") // read line is empty, read another line
        getline(InFile, line);
    int SIZE = 0; // initialize SIZE of list to 0

    istringstream is(line);
    // loop over the line reading integers into array
    //list and computing the length of the list
    while (is >> list[SIZE])
        SIZE++;
    return SIZE;
}

//##################################################//
// FUNCITION NAME
// 
// ->  int Calculate_GCD(int a, int b)
// 
// Parameters
// -> accepts in two integer values to be computed
// -> that compares to each value in the line
// 
// what it does
// 
// -> the purpose of this function is to compute
//  to determine out of the list what the greates
//  common denominator among the list is
// 
// -return type
//   -> returns the integer value of the computation
//   -> that will then be utilized in the max,min func.       
// 
// ####################################################//

int Calculate_GCD(int a, int b)
{
    if (b == 0)// if the next number is =0
        return a;//return the first value
     //cout <<" a is" << a<< endl;
     //cout <<" b is "<<  b<< endl;

    //else
    return Calculate_GCD(b, a % b);

}
//##############################################//
// function name-
// 
// -> int Calculate_LCM(int a, int b)
// 
// Parameters
// -> this function takes in the parameters
// -> a and b as integers to do comparisions
// 
// what is does?
// 
// -> the purpose of this function is to read in
// -> the integer a and b values in the list,
// -> compute the lcm of the integers and then
// -> dividing the a*b  by the gcd function for 
// -> the line that it is looking at
// 
// RETURN VALUE
// 
// -> this function returns back the integer value
// -> that will be utilized in the gcd and lcm
// -> computation function
// ################################################//

int Calculate_LCM(int a, int b)
{
  
    //first number times second number divided by GCD of the two
    return (a * b) / Calculate_GCD(a, b);

}

//############################################################//
// function name- 
// 
// ->void MaxGCDandMinLCM(int* list, int n, int& MinimumLCM, 
//                          int& MaxGCD)
// 
// Parameters-
// 
// -> this function takes in a pointer type to the list of
// ->read infile integers array
// -> reads in the number, and the memory loaction of 
// -> both the maxGCD and minLCM
// 
// What it does-
// 
// -> the main purpose of this function is to read in the 
// -> computed lcm and gcm, then compare it to the other
// -> numbers in the list and see which one is greater or less
// -> then store the max and min in a call back function that
// -> get utilized back in main
// 
// Return values
// 
// -> this function does not return andything because it is void
// 
// ############################################################//


// here we also use the pointer that points inside of the list and 
//address of min and max
void MaxGCDandMinLCM(int* list, int n, int& MinimumLCM, int& MaxGCD)
{
    MaxGCD = 0; // initialize MaxGCD to 0

    //compare the computed current Calculate_LCM and gcd value
    int Current_GCD, CurrentLCM;

    // loop from 0 to the second to last in the list
    for (int i = 0;i < n - 1;i++)
    {
        // loop from i+1 to list end
        for (int j = i + 1;j < n;j++)
        {
            //initialize the value to compare to computed
            //
            Current_GCD = Calculate_GCD(list[i], list[j]);
            CurrentLCM = Calculate_LCM(list[i], list[j]);
            // read the first entry of the line
            if (MaxGCD == 0)//if calculated is 0
            {
                //if GCD  is 0, then will set currrents
                MaxGCD = Current_GCD;
                MinimumLCM = CurrentLCM;
            }
            else
            {
                // curr GCD > max GCD, update MaxGCD


                // if the current least common mult is less than
                //min Calculate_LCM then update Calculate_LCM 
                //to be current
                if (CurrentLCM < MinimumLCM)
                    MinimumLCM = CurrentLCM;

                if (Current_GCD > MaxGCD)
                    MaxGCD = Current_GCD;

            }
        }
    }
}

