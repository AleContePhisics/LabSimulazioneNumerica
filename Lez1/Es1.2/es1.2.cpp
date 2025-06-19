#include"random.h"
#include<numeric>


int main(){

    //GENERATORE NUMERI CASUALI//

    Random rnd;
    ifstream Primes("Primes");
    int seed[4];
    int p1, p2;
    if (Primes.is_open()){
       Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();
   
    ifstream input("seed.in");
    string property;
    if (input.is_open()){
        while ( !input.eof() ){
            input >> property;
            if( property == "RANDOMSEED" ){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd.SetRandom(seed,p1,p2);
            }
        } 
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;

    //CALCOLO S PER LA DISTRIBUZIONE ESPONENZIALE//

    int M=10000;
    double r;
    double lambda=1;
    double Sum;
    vector<double> Sexp(4*M,0.);
    int N=1;

   
    for(int i=0;i<4;i++){
        if(i==1)N=2;
        if(i==2)N=10;
        if(i==3)N=100;
        for(int j=0;j<M;j++){
            for(int k=0;k<N;k++){
                r=rnd.Exponential(lambda);
                Sum+=r;
            }
            Sum=Sum/N;
            Sexp[M*i+j]=Sum;
            Sum=0.;   
        }
    }

    //CALCOLO S PER LA DISTRIBUZIONE LORENTZIANA//

    vector<double> Sltz(4*M,0.);
    double mean=0;
    double gamma=1;
    N=1;

    for(int i=0;i<4;i++){
        if(i==1)N=2;
        if(i==2)N=10;
        if(i==3)N=100;
        for(int j=0;j<M;j++){
            for(int k=0;k<N;k++){
                r=rnd.Lorentzian(mean,gamma);
                Sum+=r;
            }
            Sum=Sum/N;
            Sltz[M*i+j]=Sum;
            Sum=0.;   
        }
    }

    //CALCOLO S PER LA DISTRIBUZIONE UNIFORME//

    N=1;
    vector<double> Sunf(4*M,0.);
    for(int i=0;i<4;i++){
        if(i==1)N=2;
        if(i==2)N=10;
        if(i==3)N=100;
        for(int j=0;j<M;j++){
            for(int k=0;k<N;k++){
                r=rnd.Rannyu();
                Sum+=r;
            }
            Sum=Sum/N;
            Sunf[M*i+j]=Sum;
            Sum=0.;   
        }
    }
    //PASSAGGIO DATI PER I GRAFICI SU DATI.CSV//

    ofstream file("dati2.csv");

    for(int i=0;i<M;i++){
        file << Sexp[i]<<","<<Sexp[i+M]<<","<<Sexp[i+M*2]<<","<<Sexp[i+M*3]<<","<< Sunf[i]<<","<<Sunf[i+M]<<","<<Sunf[i+M*2]<<","<<Sunf[i+M*3]<<","<< Sltz[i]<<","<<Sltz[i+M]<<","<<Sltz[i+M*2]<<","<<Sltz[i+M*3]<<endl;
    }
    
    file.close();
    
    return 0;
}