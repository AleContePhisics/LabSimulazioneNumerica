#include "random.h"
#include<cmath>
Random :: Random(){}
// Default constructor, does not perform any action

Random :: ~Random(){}
// Default destructor, does not perform any action

void Random :: SaveSeed(){
   // This function saves the current state of the random number generator to a file "seed.out"
   ofstream WriteSeed;
   WriteSeed.open("seed.out");
   if (WriteSeed.is_open()){
      WriteSeed << "RANDOMSEED	" << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
   } else cerr << "PROBLEM: Unable to open random.out" << endl;
  WriteSeed.close();
  return;
}

double Random :: Gauss(double mean, double sigma) {
   // This function generates a random number from a Gaussian distribution with given mean and sigma
   double s=Rannyu();
   double t=Rannyu();
   double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
   return mean + x * sigma;
}

double Random :: Rannyu(double min, double max){
   // This function generates a random number in the range [min, max)
   return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
  // This function generates a random number in the range [0,1)
  const double twom12=0.000244140625;
  int i1,i2,i3,i4;
  double r;

  i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
  i2 = l2*m4 + l3*m3 + l4*m2 + n2;
  i3 = l3*m4 + l4*m3 + n3;
  i4 = l4*m4 + n4;
  l4 = i4%4096;
  i3 = i3 + i4/4096;
  l3 = i3%4096;
  i2 = i2 + i3/4096;
  l2 = i2%4096;
  l1 = (i1 + i2/4096)%4096;
  r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

  return r;
}

void Random :: SetRandom(int * s, int p1, int p2){
  // This function sets the seed and parameters of the random number generator
  m1 = 502;
  m2 = 1521;
  m3 = 4071;
  m4 = 2107;
  l1 = s[0];
  l2 = s[1];
  l3 = s[2];
  l4 = s[3];
  n1 = 0;
  n2 = 0;
  n3 = p1;
  n4 = p2;

  return;
}

double upandunder(double y){
    if(y>=0.5){
        y=1;
    } else {y=0;}
    return y;
}

double StatisticError(vector<double>&A,vector<double>&A2,int n){
    double err;
    if(n==0){err=0;}
    else {
        err=sqrt((A2[n]-pow(A[n],2))/double(n));
    }
    return err;
}


double f(double x){
    double g=(M_PI*(cos((M_PI/2.)*x)))/2.;
    return g;
}

double p(double x){
  double l=(6*(-pow(x,2)+M_PI/2.))/(3*M_PI-2);
  //double l=(1-(pow(M_PI*x,2))/8)/(1-pow(M_PI,2)/24.);
  return l;
}

double g(double x){
  double h=f(x)/p(x);
  return h;
}

vector<double>GBM(double mu,double sigma, int n,double S_0,double t_0,double t_f,Random& rnd){
  double z;
  double t=(t_f-t_0)/n;
  vector<double>S(n+1);
  S[0]=S_0;
  for(int i=0;i<n;i++){
    z=rnd.Gauss(0.,1.);
    S[i+1]=(S[i])*exp((mu-0.5*sigma*sigma)*(t)+sigma*z*sqrt(t));
  }
  
  return S;
}

double N(double x){
  double f=0.5*(1+erf(x/sqrt(2)));
  return f;
}

double EurCallOption(double mu,double sigma,double K,double t_0,double t_f,double S_0){
  double t=t_f-t_0;
  double d1;
  double d2;
  double C;

    d1=(log(S_0/K)+mu+sigma*sigma*(t)/2.)/(sigma*sqrt(t));
    d2=d1-sigma*sqrt(t);
    C=S_0*N(d1)-K*N(d2)*exp(-mu*(t));

  return C;

}

double EurPutOption(double mu,double sigma,double K,double t_0,double t_f,double S_0){
  double t=t_f-t_0;
  double d1;
  double d2;
  double C;

    d1=(log(S_0/K)+mu+sigma*sigma*(t)/2.)/(sigma*sqrt(t));
    d2=d1-sigma*sqrt(t);
    C=S_0*(N(d1)-1)-K*(N(d2)-1)*exp(-mu*(t));

  return C;

}