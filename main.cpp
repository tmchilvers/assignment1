#define _USE_MATH_DEFINES //allows access to PI constant
#include <iostream>
#include <stdexcept> //Allows access to c++ standard exception library
#include <fstream>  //Allows access to input and write to files
#include <math.h> //Used for square root
#include <string> //Allows access to strings
#include <ctime> //Take in time for seed for random numbers
using namespace std;


/*----------------------------CLASS DNA_STATS---------------------------------*/
class DnaStats
{
  private:
    string d; //all the dna strings
    int l; //all dna lengths

  public:
    //constructors
    DnaStats(); //Default
    DnaStats(int l); //Length only
    DnaStats(string d); //String only
    DnaStats(string d, int l);

    //mutator methods
    double mean(int l, int num); //caclulates mean of all DNA lengths
    double variance(double sumString, int num); //calculates variance of DNA lengths
    double standardDeviation(double var);
    double probability(int n, int sumString);
    double gaussian(double var, double stanD);

    //accessor methods
    int getLength();
    string getDna();
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

DnaStats::DnaStats(string s) //Constructor with only string provided
{
  d = s;
}

DnaStats::DnaStats(string s, int len) //Constructor for both length and string
{
  d = s;
  l = len;
}

//Accessor Methods
int DnaStats::getLength()
{
  return l;
}

string DnaStats::getDna()
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

double DnaStats::standardDeviation(double var)
{
  return sqrt(var);
}

double DnaStats::probability(int n, int sumString)
{
  return ((double)n / (double)sumString) * 100;
}

double DnaStats::gaussian(double var, double stanD)
{
  srand(time(NULL));
  double randA = ((double)rand()/(double)RAND_MAX);
  double randB = ((double)rand()/(double)RAND_MAX);

  double c = sqrt((-2 * log(randA))) * cos(2 * M_PI * randB);
  cout << "C: " << c << endl;

  double d = stanD + (var * c);

  cout << "D: " << d << endl;
  return d;
}

/*-------------------------------------MAIN-----------------------------------------*/
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

    int countA = 0, countT = 0, countC = 0, countG = 0; //initialize all counting objects for each nucleotide to zero
    int countAA = 0, countAC = 0, countAT = 0, countAG = 0;
    int countTA = 0, countTC = 0, countTT = 0, countTG = 0;
    int countCC = 0, countCA = 0, countCT = 0, countCG = 0;
    int countGG = 0, countGA = 0, countGT = 0, countGC = 0;

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
          dna[i] = tolower(dna[i]); //convert all to lowercase to read through more easily

          //find probability of each nucleotide by summing each nucleotide
          if(dna[i] == 'a')
          {
            countA += 1;
          }

          else if(dna[i] == 't')
          {
            countT += 1;
          }

          else if(dna[i] == 'c')
          {
            countC += 1;
          }

          else if(dna[i] == 'g')
          {
            countG += 1;
          }
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

      for(int i = 0; i < dna.size(); i++)
      {
        //Check for bigrams
        if(dna[i+1] == '\r')
        {
          //pass
        }

        else if(dna[i] == 'a' && dna[i+1] == 'a')
        {
          countAA += 1;
        }

        else if(dna[i] == 'a' && dna[i+1] == 'c')
        {
          countAC += 1;
        }

        else if(dna[i] == 'a' && dna[i+1] == 't')
        {
          countAT += 1;
        }

        else if(dna[i] == 'a' && dna[i+1] == 'g')
        {
          countAG += 1;
        }

        else if(dna[i] == 'c' && dna[i+1] == 'c')
        {
          countCC += 1;
        }

        else if(dna[i] == 'c' && dna[i+1] == 'a')
        {
          countCA += 1;
        }

        else if(dna[i] == 'c' && dna[i+1] == 't')
        {
          countCT += 1;
        }

        else if(dna[i] == 'c' && dna[i+1] == 'g')
        {
          countCG += 1;
        }

        else if(dna[i] == 'g' && dna[i+1] == 'g')
        {
          countGG += 1;
        }

        else if(dna[i] == 'g' && dna[i+1] == 'c')
        {
          countGC += 1;
        }

        else if(dna[i] == 'g' && dna[i+1] == 't')
        {
          countGT += 1;
        }

        else if(dna[i] == 'g' && dna[i+1] == 'a')
        {
          countGA += 1;
        }

        else if(dna[i] == 't' && dna[i+1] == 't')
        {
          countTT += 1;
        }

        else if(dna[i] == 't' && dna[i+1] == 'c')
        {
          countTC += 1;
        }

        else if(dna[i] == 't' && dna[i+1] == 'a')
        {
          countTA += 1;
        }

        else if(dna[i] == 't' && dna[i+1] == 'g')
        {
          countTG += 1;
        }
      }
    }

    double probA, probT, probC, probG; //initialize probability objects of nucleotides
    double probAA, probAC, probAT, probAG, probCC, probCA, probCT, probCG, probGG, probGA, probGT, probGC, probTT, probTA, probTC, probTG;


    DnaStats inputtedDna(allDna, sum); //DnaStats object created to calculate math and stats data

    probA = inputtedDna.probability(countA, sum); //find probability of each nucleotide
    probT = inputtedDna.probability(countT, sum);
    probC = inputtedDna.probability(countC, sum);
    probG = inputtedDna.probability(countG, sum);
    probAA = inputtedDna.probability(countAA, sum); //find probability of each brigram
    probAC = inputtedDna.probability(countAC, sum);
    probAT = inputtedDna.probability(countAT, sum);
    probAG = inputtedDna.probability(countAG, sum);
    probCC = inputtedDna.probability(countCC, sum);
    probCA = inputtedDna.probability(countCA, sum);
    probCT = inputtedDna.probability(countCG, sum);
    probGG = inputtedDna.probability(countGG, sum);
    probGA = inputtedDna.probability(countGA, sum);
    probGT = inputtedDna.probability(countGC, sum);
    probGC = inputtedDna.probability(countGC, sum);
    probTT = inputtedDna.probability(countTT, sum);
    probTA = inputtedDna.probability(countTA, sum);
    probTC = inputtedDna.probability(countTC, sum);
    probTG = inputtedDna.probability(countTG, sum);

    cout << "Sum: " << sum << endl;

    double mean = 0;
    mean = inputtedDna.mean(sum, numOfStrings); //calculate mean of all dna lengths
    cout << "Mean: " << mean << endl;


    dnaFile.close(); //Must close and reopen file to use getline method again
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

    double stanDev = 0;
    stanDev = inputtedDna.standardDeviation(variance);
    cout << "Standard Deviation: " << stanDev << endl;

    inputtedDna.gaussian(variance, stanDev);



    cout << "Enter another file? (y|n): " << endl; //Allow user to enter another file again.
    cin >> answer;

    if(answer == 'y' || answer == 'Y')
    {
      cout << "\nPlease enter file name (must be .txt): " << endl;
      cin >> argv[1];
    }

    else if(answer == 'n' || answer == 'N')
    {
      break;
    }

    else
    {
      cout << "Not a valid answer. Program fail.\n";
      exit(1);
    }

  } while(answer == 'y' || answer == 'Y');


  cout << "\nProgram will now close.\n";


  return 0;
}
