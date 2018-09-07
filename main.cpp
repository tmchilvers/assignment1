#include <iostream>
#include <stdexcept> //Allows access to c++ standard exception library
#include <fstream>  //Allows access to input and write to files
using namespace std;

int main(int argc, char* argv[])
{
  try
  {
    if(argc < 2) //The program must have two arguments: program name and text file name
    {
      throw invalid_argument("A second argument is required. Must be a .txt file of DNA strings\n"); //exception for incorrect number of arguments
    }

    else //Must check if second argument is a text file
    {
      ifstream inputtedFile(argv[1]);  //set inputtedFile to the file from the second argument

      if(!inputtedFile.is_open())
      {
        throw invalid_argument("Second argument must be of file type: .txt\n"); //exception for incorrect file type
      }

      else
      {
        //continue program
        cout << "Program will continue here!!\n" << endl;
      }
    }
  }

  catch(const invalid_argument& e) //catch the exceptions here
  {
    cerr << e.what() << endl; //this will print out error message
  }



  return 0;
}
