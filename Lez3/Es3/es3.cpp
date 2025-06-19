#include "random.h"
#include<numeric>

int main(){

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

    //     CODICE     //

    ofstream out;
    ofstream out2;
    ofstream out3;
    out.open("Output/dati.csv");
    out3.open("Output/ndati.csv");
    double r=0.1,sigma=0.25;
    double K=100.,S0=100.,t_0=0.,T=1.;
    int N=100; //numero di blocchi per la statistica
    int n=1; //numero di divisioni nel calcolo si S(t)
    int M=10000;  //numero di ripetizioni della singola simulazione per un solo blocco N

    vector<double>S(n+1);  //andamento mercato per n=1
    vector<double>Sn(n+1); //andamento mercato per n generico
    double C,P;
    double sum=0,sum2=0;
    vector<double> Call1(N),Call2(N),Call1n(N),Call2n(N);  //valori delle call (n indica per n divisioni di S(t))
    vector<double> sq(N),sq2(N),sq1n(N),sq2n(N);  //vector per errore statistico nelle call
    vector<double> Put1(N),Put2(N),Put1n(N),Put2n(N);  //valori dei put (n indica per n divisioni di S(t))
    vector<double> sq3(N),sq3n(N),sq4(N),sq4n(N);  //vector per errore statistico nel put
    vector<double> err(N),err2(N),err1n(N),err2n(N);   //errore statistico  (n indica per n divisioni di S(t))

    out2.open("Output/input.dat");

    C=EurCallOption(r,sigma,K,t_0,T,S0);   //valori teorici call and put option
    P=EurPutOption(r,sigma,K,t_0,T,S0);
    out2<<N<<","<<C<<","<<P<<endl;  //passaggio al python di N blocchi e valori teorici


    for(int i=0;i<N;i++){  //call  option//

        sum=0;
        sum2=0;
        for(int j=0;j<M;j++){
            S=GBM(r,sigma,1,S0,t_0,T,rnd);

            Sn=GBM(r,sigma,n,S0,t_0,T,rnd);
        
            sum+=exp(-r*T)*max(S[n]-K,0.);

            sum2+=exp(-r*T)*max(Sn[n]-K,0.);
        }

        Call1[i]=sum/M;
        sq[i]=pow(Call1[i],2);
        Call2[i]=accumulate(Call1.begin(),Call1.end(),0.)/(i+1);
        sq2[i]=accumulate(sq.begin(),sq.end(),0.)/(i+1);
        err[i]=StatisticError(Call2,sq2,i);

        Call1n[i]=sum2/M;
        sq1n[i]=pow(Call1n[i],2);
        Call2n[i]=accumulate(Call1n.begin(),Call1n.end(),0.)/(i+1);
        sq2n[i]=accumulate(sq1n.begin(),sq1n.end(),0.)/(i+1);
        err1n[i]=StatisticError(Call2n,sq2n,i);
        
    }
 
    for(int i=0;i<N;i++){  //put option//
        sum=0;
        sum2=0;
        for(int j=0;j<M;j++){

            S=GBM(r,sigma,1,S0,t_0,T,rnd);

            Sn=GBM(r,sigma,n,S0,t_0,T,rnd);
        
            sum+=exp(-r*T)*abs(min(S[n]-K,0.));

            sum2+=exp(-r*T)*abs(min(Sn[n]-K,0.));
        }

        Put1[i]=sum/M;
        sq3[i]=pow(Put1[i],2);
        Put2[i]=accumulate(Put1.begin(),Put1.end(),0.)/(i+1);
        sq4[i]=accumulate(sq3.begin(),sq3.end(),0.)/(i+1);
        err2[i]=StatisticError(Put2,sq4,i);

        Put1n[i]=sum2/M;
        sq3n[i]=pow(Put1n[i],2);
        Put2n[i]=accumulate(Put1n.begin(),Put1n.end(),0.)/(i+1);
        sq4n[i]=accumulate(sq3n.begin(),sq3n.end(),0.)/(i+1);
        err2n[i]=StatisticError(Put2n,sq4n,i);

        out<<Call2[i]<<","<<err[i]<<","<<Put2[i]<<","<<err2[i]<<endl;      //passaggio dati ai file
        out3<<Call2n[i]<<","<<err1n[i]<<","<<Put2n[i]<<","<<err2n[i]<<endl;
        
    }

    

    









    return 0;
}