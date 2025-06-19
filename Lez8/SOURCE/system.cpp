#include "system.h"
#include <cmath>
#include <numeric>
using namespace std;

void System :: initialize(){
    int p1, p2; // Read from ../INPUT/Primes a pair of numbers to be used to initialize the RNG
    ifstream Primes("../INPUT/Primes");
    Primes >> p1 >> p2 ;
    Primes.close();
    int seed[4]; // Read the seed of the RNG
    ifstream Seed("../INPUT/seed.in");
    Seed >> seed[0] >> seed[1] >> seed[2] >> seed[3];
    rnd.SetRandom(seed,p1,p2);

}

double System :: delta(){

    double x=rnd.Gauss(0,0.1);
    return x;
}

double System :: TestFunction(double mu,double sigma,double x1){

    double y;
    y=exp(-pow(x1-mu,2)/(2*pow(sigma,2)))+exp(-pow(x1+mu,2)/(2*pow(sigma,2)));
    if(y < 1e-15)y = 1e-15; // evita divisioni per numeri troppo piccoli
    
    return y;

}

double System :: SecDerTestFunction(double mu, double sigma, double x) {
  double s2 = sigma * sigma;
  double s4 = s2 * s2;

  double a = ( ( (x - mu)*(x - mu) - s2 ) / (s4) ) * exp( - (x - mu)*(x - mu) / (2 * s2) );
  double b = ( ( (x + mu)*(x + mu) - s2 ) / (s4) ) * exp( - (x + mu)*(x + mu) / (2 * s2) );
  return a + b;
}

double System :: Metro(double mu,double sigma,double x0){

    double delta=rnd.Gauss(0.,1.5);
    double x1=x0+delta;

    
    double r=rnd.Rannyu();
    double A;
    
    double p=pow(TestFunction(mu,sigma,x1),2)/pow(TestFunction(mu,sigma,x0),2);

    if(p<1) A=p;
    else if(p>=1)  A=1;

    if(r<A){
        accept++;
        return x1;
    }
    else return x0;

}

double System :: Potential (double x){
    double V=pow(x,4)-5.*pow(x,2)/2.;
    return V;
}

double System :: Hm (double mu,double sigma,double x0){
    double H=0;
    double x=x0;

    for(int i=0;i<10000;i++){
        x=Metro(mu,sigma,x);
        H+=-0.5*SecDerTestFunction(mu,sigma,x)/TestFunction(mu,sigma,x)+Potential(x);
        } 
    H/=10000;
    accept=0;
    return H;
}

void System :: Swap(Hamiltonian& H1,Hamiltonian& H2){
    double x;
    x=H1.GetMu();
    H1.SetMu(H2.GetMu());
    H2.SetMu(x);
    x=H1.GetSigma();
    H1.SetSigma(H2.GetSigma());
    H2.SetSigma(x);
    x=H1.GetMean();
    H1.SetMean(H2.GetMean());
    H2.SetMean(x);
};

double StatisticError(double a,double b,int n){
    double err;
    if(n==0){err=0;}
    else {
        err=sqrt((b-pow(a,2))/double(n));
    }
    return err;
}

double StatisticError(vector<double>A,vector<double>B,int n){
    double err;
    if(n==0){err=0;}
    else {
        err=sqrt((B[n]-pow(A[n],2))/double(n));
    }
    return err;
}
