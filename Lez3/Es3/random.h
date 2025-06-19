#include<iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

class Random {

    private:
      int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;
    
    protected:
    
    public:
      // Default constructor
      Random();
      // Destructor
      ~Random();
      // Method to set the seed for the RNG
      void SetRandom(int * , int, int);
      // Method to save the seed to a file
      void SaveSeed();
      // Method to generate a random number in the range [0,1)
      double Rannyu(void);
      // Method to generate a random number in the range [min,max)
      double Rannyu(double min, double max);
      // Method to generate a random number with a Gaussian distribution
      double Gauss(double mean, double sigma);
    };
    
double StatisticError(vector<double>&A,vector<double>&A2,int n);
double f(double x);
double p(double x);
double g(double x);
double N(double x);
vector<double> GBM(double mu,double sigma,int N,double S_0,double t_0,double t,Random& rnd);
double EurCallOption(double mu,double sigma,double K,double t_0,double t_f,double S_0);
double EurPutOption(double mu,double sigma,double K,double t_0,double t_f,double S_0);