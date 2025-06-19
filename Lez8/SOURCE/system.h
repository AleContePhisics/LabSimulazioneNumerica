#include <iostream>
#include <armadillo>
#include <vector>
#include <cmath>
#include <numeric>
#include "random.h"

using namespace std;

class Hamiltonian {

    public:

    Hamiltonian(double x,double y){mu=x,sigma=y;}

    void SetMu(double x){mu=x;}
    void SetSigma(double x){sigma=x;}
    void SetMean(double x){mean=x;}
    double GetMu(){return mu;}
    double GetSigma(){return sigma;}
    double GetMean(){return mean;}

    protected:

    double mu;
    double sigma;
    double mean;

};


class System {
    
    public:

    void initialize();
    double TestFunction (double mu,double sigma,double x);
    double SecDerTestFunction(double mu,double sigma,double x);
    double Metro (double mu, double sigma,double x);
    double Potential (double x);
    double Hm (double mu,double sigma,double x0);
    void Swap(Hamiltonian& H1,Hamiltonian& H2);
    double delta();
    double Uniform(){return rnd.Rannyu();}
    double Uniform(double a,double b){return rnd.Rannyu(a,b);}

    protected:

    Random rnd;
    double accept=0.;

};

double StatisticError(double a,double b,int n);





