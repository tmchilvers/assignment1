#include <iostream>
#include <stdexcept> //Allows access to c++ standard exception library
#include <fstream>  //Allows access to input and write to files
using namespace std;

int main(int argc, char* argv[]) //Will take in 2 arguments
{

  char answer; //This is the answer given by the user to either restart or end program. Must be defined outside of loop

  do { //this do-while loop allows program to be repeated again.

    try
    {
      if(argc < 2 || argc > 2) //The program takes two arguments: program name and text file name
      {
        throw invalid_argument("Two arguments are required. Second arg must be a .txt file of DNA strings\n"); //exception for incorrect number of arguments
      }

      else //Must check if second argument is a text file
      {
        ifstream dnaFile(argv[1]);  //set inputtedFile to the file from the second argument

        if(!dnaFile.is_open())
        {
          throw invalid_argument("Second argument must be of file type .txt, and/or exist in directory.\n"); //exception for incorrect file type
        }
      }
    }

    catch(const invalid_argument& e) //catch the exceptions here
    {
      cerr << e.what() << endl; //this will print out error message
      cerr << "Fatal error - Program exits\n";
      exit(1);
    }

    ifstream dnaFile; //set input file to dnaFile
    dnaFile.open(argv[1]); //open file

    string dna;

    while(getline(dnaFile, dna)) //Read each line in file
    {
      for(int i = 0; i < dna.size(); i++) //Iterate through all the letters of each line
      {
        if(dna[dna.size()-1] == '\r') //Windows issue: Get line stops and discards \n, but not \r. Must change size everytime there is \r.
        {
          dna.resize(dna.size()-1);
        }

        //check if letters are correct letters found in DNA, accounting for capital and lowercase
        if(dna[i] == 'A' || dna[i] == 'a' || dna[i] == 'C' || dna[i] == 'c' || dna[i] == 'G' || dna[i] == 'g' || dna[i] == 'T' || dna[i] == 't')
        {
          //class functions for individual string data will be used here
        }

        else
        {
          cout << "Error in DNA. Incorrect letter was detected in DNA string.\nProgram will end." << endl;
          exit(1);
        }
      }
      cout << dna << endl;
    }





    cout << "Enter another file? (y|n): " << endl; //Allow user to enter another file again.
    cin >> answer;

    if(answer == 'y' || answer == 'Y')
    {
      cout << "\nPlease enter file name (must be .txt): " << endl;
      cin >> argv[1];
    }

    else
    {
      //program will continue
    }

  } while(answer == 'y' || answer == 'Y');

  cout << "\nProgram will now close.\n";


  return 0;
}
