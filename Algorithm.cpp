// Algorithm Lab6
// Shiwei Huang
// Purpose:
// 1. Implement the Brute force string matching algorithm
// 2. Closest pair algorithms

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> /* printf */
#include <math.h>

using namespace std;

// ** StringMatchingBF Function **
// Input: two strings
// Output: return the index of the first location in the first string where the second input string is found;
int StringMatchingBF (string , string );

int StringMatchingBF ( string str1, string str2 ) {
	for ( int i = 0; i < str1.length() - str2.length(); i++ ) {
		int j = 0;
		while (( j < str2.length() ) && ( str1[i+j] == str2[j] )) {
			j++;
		}

		if ( j == str2.length() ) {
			return i;
		}
	}
	return -1; // if not found, return -1;
}

/** BEGINING FROM HERE IS CLOSEST PAIR ALGORITHM **/
/* class point2D */
// Contains two public data members: an x coordinate and a y coordinate, both integers
class point2D {
public:
	int xCoordinate, yCoordinate;
	//write a constructor that takes two integers as input and uses them to initialize the xCoordinate and yCoordinate of the point;
	point2D ( int x, int y ) { xCoordinate = x; yCoordinate = y;}; //constructor
	string toString (); //toString function

};
/* toString() function */
// input: takes no input;
// output: a string representing the point;
// for example, toString should return the string "(11, 5)" if my x coordinate of the point is 11, and the y coordinate of the point is 5;
string point2D :: toString () {
	string intToStringFirstValue, intToStringSecondValue; //to store converted results;
	ostringstream convertXCoordinate, convertYCoordinate;
	convertXCoordinate << xCoordinate;
	convertYCoordinate << yCoordinate;

	intToStringFirstValue = convertXCoordinate.str();
	intToStringSecondValue = convertYCoordinate.str(); 
	return "(" + intToStringFirstValue + "," + intToStringSecondValue + ")";
}

/* ClosestPairBF function */
// input: an array of pointers to point2D, array's size, two other integers passed by reference
// output: not returning anything. However, in the main(){}, （because the function call is pass by reference）return the indices of the closest points 
// (because locationForPt1, locationForPt2 is pass by reference).
void ClosestPairBF ( point2D **arrayOfPointers, int size, int &locationForPt1, int &locationForPt2 ) {
	// by assumption, minDistance is two points distance from first and second location from my array;
	int minDistance = ((arrayOfPointers[0] -> yCoordinate - arrayOfPointers[1] -> yCoordinate) * (arrayOfPointers[0] -> yCoordinate - arrayOfPointers[1] -> yCoordinate)) +
					  ((arrayOfPointers[0] -> xCoordinate - arrayOfPointers[1] -> xCoordinate) * (arrayOfPointers[0] -> xCoordinate - arrayOfPointers[1] -> xCoordinate));
	locationForPt1 = 0; 
	locationForPt2 = 1;
	
	for ( int i = 0; i <= size - 2; i++ ) {
		for ( int j = i+1; j <= size - 1; j++ ) {

			if ( minDistance > ((arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate) * (arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate)) +
			   ((arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate) * (arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate)))
			{	
				minDistance = ((arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate) * (arrayOfPointers[i] -> yCoordinate - arrayOfPointers[j] -> yCoordinate)) +
					          ((arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate) * (arrayOfPointers[i] -> xCoordinate - arrayOfPointers[j] -> xCoordinate));
				locationForPt1 = i;
				locationForPt2 = j;
			}//if
				
		}//for
	}//for
	
}//void



int main () {
	// main function should ask the user for the name of an input file;
	// and ask if that file is a text file, or a file of numbers.
	int fileNumber;
	string fileOneName, fileTwoName;
	cout << "And type 1 if the input file is a file of numbers" << endl;
	cout << "Type 2 if the input file is a text file" << endl;


	cin >> fileNumber;
	if ( fileNumber == 1 ) { //file is a file of numbers.
		cout << "Type in the name of the input file: " << endl;
		cin >> fileOneName;
		ifstream myFile (fileOneName);
		int total2DPointsInFile;
		point2D **arrayToStore2DPoint; //construct an array of pointers to point2D;
		if ( myFile.is_open() ) {
			myFile >> total2DPointsInFile; //read in the first line of the file; which contain the number of other lines in the file;
			arrayToStore2DPoint = new point2D* [total2DPointsInFile];
			int firstNum, secondNum;
			for ( int i = 0; i < total2DPointsInFile; i++ ) {
				myFile >> firstNum >> secondNum;
				// QUESTION: IS MY EXPLANATION CORRECT for the following code??
				arrayToStore2DPoint[i] = new point2D ( firstNum, secondNum ); //allocating 'firstNum' and 'secondNum' in array of pointers to point2D in [0],[1],[2] location...etc;
			}


			/*********************** BEGING TEST: PRINTING THE WHOLE ARRAY OF POINTERS ***********************/

			/* IF NEEDED TO PRINT OUT THE ENTIRE ARRAY OF POINTERS (that's how you do) */

			// print out entire array of pointers;
			// for ( int i = 0; i < total2DPointsInFile; i++ ) {
			// 		cout << arrayToStore2DPoint[i] -> toString() << endl;  //each line should be written using the toString function of each object;
			// }

			/*********************** END TEST: PRINTING THE WHOLE ARRAY OF POINTERS ***********************/


			int location1ForFunction, location2ForFunction;
			ClosestPairBF ( arrayToStore2DPoint, total2DPointsInFile, location1ForFunction, location2ForFunction );

			cout << "location1: " << location1ForFunction << endl; // print on screen the two indices
			cout << "location2: " << location2ForFunction << endl;
			// also print on screen the points that are closest.
			cout << "In conclusion, for the points that are closest are: " << arrayToStore2DPoint[location1ForFunction] -> toString();
			cout << " " << arrayToStore2DPoint[location2ForFunction] -> toString() << endl;
		}//if could allocate file;
		else {
			cout << "Sorry. Cannot locate your number file." << endl;
		}//else (file is not found)

	} //if; numbers file;


	 else { //a file of text;
	 	cout << "Type in the name of the input file: " << endl;
		cin >> fileTwoName;
		ifstream myFile (fileTwoName);
		int totalLineInFile;
		string stringInFile;


		// IMPORTANT Notes in class: 
		//  for example, this is how your file looks like;
		// 	4\n
		// 	This\n
		// 	Is\n
		// 	a\n
		// 	test\n
		// So that getline(infile, line); treat the 4\n line's '\n' as another line;

		string emptyString = ""; 

		// *************** Begin Tutorial: *****************

		// ifstream infile;
		// getline function:
		// getline(infile, s);
		// s: by default, getline read s until it's '\n';

		// *************** END Tutorial: *****************


		if ( myFile.is_open() ) {	
			myFile >> totalLineInFile; // the first line of the file will contain the number of other lines in the file;
			getline (myFile, emptyString); // Martin's note: read the rest of the empty first line;

/* The following part read the entire file and store the text in a single string */

			for ( int i = 0; i < totalLineInFile; i++ ) {
					getline ( myFile, stringInFile ); // construct the text from .txt file into string;
					if ( stringInFile[stringInFile.length()-1] == ' ' ) { //if stringInFile has has a space by the end of the line; I am not adding a space in my string'stringInFile'
						emptyString = emptyString + stringInFile;
					}

					else {
						// if by the end of my file the user didn't contain " ";
						emptyString = emptyString + stringInFile + " "; // adding " " manually to make sure words in 'emptyString' are separated by a single space;
					}
			}//for
			
// ************************* BEGIN TEST STATEMENT TO SEE MY 'emptyString' *************************

// 			cout << "**************************** TESTING TO SEE EMPTYSTRING ****************************" << endl;
// 			cout << emptyString << endl;
// 			cout << "**************************** END TESTING TO SEE EMPTYSTRING ****************************" << endl;

/************************* END TEST STATEMENT TO SEE MY 'emptyString' *************************/

// From lab spec sheet:
// Your program should ask the user to enter a string;
// User's string should search the text from file;
// Run the string matching function. 
			
			cout << "Now, let's search for a string in this text file. Please type in your search string." << endl;
			cout << "Search function will return the index of the first location in the first string input;" << endl;
			cout << "And -1 if the search cannot found." << endl;
			cout << "The program will keep searching for the string until user enters an empty string." << endl;

// Bizzare but IMPORTANT notes from class:
			string userSearch;
			getline(cin, userSearch); // READS FROM THE PREVIOUS 'text1.txt\n'; Just to pickup previous newline from the user input to console;
			getline(cin, userSearch); //READS everything that user puts;
			while ( userSearch != " " ) { // The program will keep searching for the string until user enters an empty string, which terminates the program.
				int indexOfUserSearch = StringMatchingBF ( emptyString, userSearch );
				cout << "The location for your string is: " << indexOfUserSearch << endl; 
				getline(cin, userSearch);  //READS everything that user puts;
			}

		}//if file is open;

		else {
			cout << "Sorry. Cannot locate your text file." << endl;
		}//else
	}// else (a file of text)

}//main();





