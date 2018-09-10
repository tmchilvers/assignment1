#include <iostream>
#include <stdexcept> //Allows access to c++ standard exception library
#include <fstream>  //Allows access to input and write to files
using namespace std;


/*----------------------------CLASS DNA_STATS---------------------------------*/
class DnaStats
{
  private:
    std::string d; //all the dna strings
    int l; //all dna lengths

  public:
    //constructors
    DnaStats(); //Default
    DnaStats(int l); //Length only
    DnaStats(std::string d); //String only
    DnaStats(std::string d, int l);

    //mutator methods
    double mean(int l, int num); //caclulates mean of all DNA lengths
    double variance(double sumString, int num); //calculates variance of DNA lengths
    double standardDeviation(int l);
    double probNucleotide(int l);
    double probBigram(int l);

    //accessor methods
    int getLength();
    std::string getDna();
};


/*---------------------------DNA_STATS DEFINITIONS----------------------------*/
DnaStats::DnaStats() //Default constructor definition
{
  d = " ";
  l = 0;
}

DnaStats::DnaStats(int len) //Constructor with only length provided
{
  l = len;
}

DnaStats::DnaStats(std::string s) //Constructor with only string provided
{
  d = s;
}

DnaStats::DnaStats(std::string s, int len) //Constructor for both length and string
{
  d = s;
  l = len;
}

//Accessor Methods
int DnaStats::getLength()
{
  return l;
}

std::string DnaStats::getDna()
{
  return d;
}

//Mutator methods
double DnaStats::mean(int totalLen, int num)
{
  return ((double)totalLen / (double)num);
}

double DnaStats::variance(double sumString, int num)
{
  return (sumString / num);
}


/*---------------------------------MAIN---------------------------------------*/
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

    string dna = ""; //this string allows program to check if the file inputted is applicable for program
    string allDna = ""; //Initialize a string to take in all of the dna strings
    int sum = 0; //initialize sum of all the lengths
    int numOfStrings = 0; //count the number of DNA strings there are

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
      sum += dna.size(); //add the size of each DNA string to the total sum
      numOfStrings += 1; //add how many DNA strings there are
      allDna += dna; //record all the DNA strings and store it in one single string object
    }

    DnaStats inputtedDna(allDna, sum); //DnaStats object created to calculate math and stats data

    double mean = 0;
    mean = inputtedDna.mean(sum, numOfStrings); //calculate mean of all dna lengths
    cout << "Mean: " << mean << endl;


    dnaFile.close();
    dnaFile.open(argv[1]); //open file

    dna = "";
    int dnaLength = 0; //find individual length of each dna string
    double sumForVariance = 0; //must find sum of all lengths' difference between mean, and be squared
    while(getline(dnaFile, dna))
    {
      for(int i = 0; i < dna.size(); i++) //Iterate through all the letters of each line
      {
        if(dna[dna.size()-1] == '\r') //Windows issue: Get line stops and discards \n, but not \r. Must change size everytime there is \r.
        {
          dna.resize(dna.size()-1);
        }
      }
      dnaLength = dna.size(); //find individual length of each string
      double difference = dnaLength - mean; //find the difference between length and mean
      double square = difference * difference; //square the result
      sumForVariance += square; //add result to total sum
    }

    double variance = 0;
    variance = inputtedDna.variance(sumForVariance, numOfStrings);
    cout << "Variance: " << variance << endl;



    cout << "Enter another file? (y|n): " << endl; //Allow user to enter another file again.
    cin >> answer;

    if(answer == 'y' || answer == 'Y')
    {
      cout << "\nPlease enter file name (must be .txt): " << endl;
      cin >> argv[1];
    }

  } while(answer == 'y' || answer == 'Y');

  cout << "\nProgram will now close.\n";


  return 0;
}
