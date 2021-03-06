#define _USE_MATH_DEFINES //Allows access to PI constant
#include <iostream>
#include <stdexcept> //Allows access to c++ standard exception library
#include <fstream>  //Allows access to input and write to files
#include <math.h> //Used for square root
#include <string> //Allows access to strings
#include <ctime> //Take in time for seed for random numbers
using namespace std;


/*----------------------------CLASS DNA_STATS---------------------------------*/
//This class will perform required mathematical functions to find data for each DNA file
class DnaStats
{
  private:
    string d; //all the DNA strings of file
    int l; //all DNA lengths of file

  public:
    //constructors
    DnaStats(); //Default
    DnaStats(int l); //Length only
    DnaStats(string d); //String only
    DnaStats(string d, int l); //Both length and string given


    //mutator methods
    double mean(int l, int num); //caclulates mean of all DNA lengths
    double variance(double sumString, int num); //calculates variance of DNA lengths
    double standardDeviation(double var); //calculates standardDeviation of DNA lengths
    double probability(int n, int sumString); //calculates the probability of any number of nucleotide or bigram of entire DNA file
    double gaussian(double var, double stanD); //calculates the length for every new string created

    //accessor methods
    int getLength(); //length of all DNA strings
    string getDna(); //All DNA strings
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

double DnaStats::gaussian(double m, double stanD)
{
  double d = 0;
  while(d < 2) //if D is less than two, find D again to prevent issue with creating new DNA strings of no length
  {
    d = 0;
    double randA = ((double)rand()/(double)RAND_MAX); //first random number
    double randB = ((double)rand()/(double)RAND_MAX); //secdon random number

    double c = sqrt((-2 * log(randA))) * cos(2 * M_PI * randB); //Gaussian equation
    d = m + (stanD * c); //find length D for new dna strings
  }
  return d;
}

/*------------------------------------MAIN------------------------------------*/
int main(int argc, char* argv[]) //Will take in 2 arguments
{
  srand(time(NULL)); //seed to time to better produce random numbers

  char answer; //This is the answer given by the user to either restart or end program. Must be defined outside of loop
  ofstream outputDnaFile; //open new file called TristanChilvers.out
  outputDnaFile.open("TristanChilvers.out", ios::in | ios::app);

  outputDnaFile << "\n\nTristan Chilvers\n";
  outputDnaFile << "2288893\n";
  outputDnaFile << "Section 02\n\n\n";

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
    probCT = inputtedDna.probability(countCT, sum);
    probCG = inputtedDna.probability(countCG, sum);
    probGG = inputtedDna.probability(countGG, sum);
    probGA = inputtedDna.probability(countGA, sum);
    probGT = inputtedDna.probability(countGT, sum);
    probGC = inputtedDna.probability(countGC, sum);
    probTT = inputtedDna.probability(countTT, sum);
    probTA = inputtedDna.probability(countTA, sum);
    probTC = inputtedDna.probability(countTC, sum);
    probTG = inputtedDna.probability(countTG, sum);

    outputDnaFile << "Sum: " << sum << endl; //print sum stats to TristanChilvers.out file

    double mean = 0;
    mean = inputtedDna.mean(sum, numOfStrings); //calculate mean of all dna lengths
    outputDnaFile << "Mean: " << mean << endl;

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

    double variance = 0; //calculate Variance
    variance = inputtedDna.variance(sumForVariance, numOfStrings);

    double stanDev = 0; //calculate standard deviation
    stanDev = inputtedDna.standardDeviation(variance);

    //Output probability of bigrams to TristanChilvers.out file
    outputDnaFile << "Variance: " << variance << endl;
    outputDnaFile << "Standard Deviation: " << stanDev << "\n\n\n";
    outputDnaFile << "Probability of each nucleotide listed below:\n\nProbability of A: " << probA << "%\n";
    outputDnaFile << "Probability of T: " << probT << "%\n";
    outputDnaFile << "Probability of C: " << probC << "%\n";
    outputDnaFile << "Probability of G: " << probG << "%\n\n\n";
    outputDnaFile << "Probability of each nucleotide bigram listed below:\n\n";
    outputDnaFile << "Probability of AA: " << probAA << "%\n";
    outputDnaFile << "Probability of AT: " << probAT << "%\n";
    outputDnaFile << "Probability of AC: " << probAC << "%\n";
    outputDnaFile << "Probability of AG: " << probAG << "%\n";
    outputDnaFile << "Probability of TT: " << probTT << "%\n";
    outputDnaFile << "Probability of TA: " << probTA << "%\n";
    outputDnaFile << "Probability of TC: " << probTC << "%\n";
    outputDnaFile << "Probability of TG: " << probTG << "%\n";
    outputDnaFile << "Probability of CC: " << probCC << "%\n";
    outputDnaFile << "Probability of CG: " << probCG << "%\n";
    outputDnaFile << "Probability of CA: " << probCA << "%\n";
    outputDnaFile << "Probability of CT: " << probCT << "%\n";
    outputDnaFile << "Probability of GG: " << probGG << "%\n";
    outputDnaFile << "Probability of GC: " << probGC << "%\n";
    outputDnaFile << "Probability of GA: " << probGA << "%\n";
    outputDnaFile << "Probability of GT: " << probGT << "%\n";

    outputDnaFile << "\n\n1000 DNA strings created below: \n\n";
    srand(time(NULL)); //set seed for random to time for better random calculations


    countA = 0; //initialize variables to count number of each nucleotide being added into the new DNA string
    countT = 0;
    countC = 0;
    countG = 0;
    double checkD = 0;
    double checkProbA = 0; //initialize new probability of each nucleotide in string
    double checkProbT = 0;
    double checkProbC = 0;
    double checkProbG = 0;
    for(int i = 0; i < 1000; i++) //make 1000 strings
    {
      int D = 0; //calculate length for new DNA string
      D = inputtedDna.gaussian(mean, stanDev); //calculate gaussian length

      for(int j = 0; j < D; j++) //make a string the length of calculated D
      {
        int randNum = ((rand() % 100) + 1); //find a random number between 1-100
        if(randNum < probA) //if less than probability of A. Methods below follow similar structure
        {
          outputDnaFile << 'A';
        }

        else if(randNum < (probT + probA))
        {
          outputDnaFile << 'T';
        }

        else if(randNum < (probC + probT + probA))
        {
          outputDnaFile << 'C';
        }

        else
        {
          outputDnaFile << 'G';
        }
      }
      outputDnaFile << '\n';
    }


    cout << "\nProgram has written data to TristanChilvers.out file. Please check your directory for this file.\n";

    dnaFile.close(); //Close input file


    cout << "Enter another file? (y|n): " << endl; //Allow user to enter another file again.
    cin >> answer;

    if(answer == 'y' || answer == 'Y') //this allows user to return to beginning of while loop and process information of new file
    {
      cout << "\nPlease enter file name (must be .txt): " << endl;
      cin >> argv[1]; //making this object equal to the file allows the program to check for error in file input again


      outputDnaFile << "\n\n\n\n\n\n--------------------------------------------\nNEW DATA\n\n\n";
    }

    else if(answer == 'n' || answer == 'N') //if n the program will end
    {
      outputDnaFile.close(); //close output file
      break;
    }

    else
    {
      outputDnaFile.close(); //close output file
      cout << "Not a valid answer. Program fail.\n"; //if anything other than y or n is given
      exit(1);
    }

  } while(answer == 'y' || answer == 'Y');



  cout << "\nProgram will now close.\n";


  return 0;
}
