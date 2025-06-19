#include "random.h"
#include<cmath>
#include<vector>
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

    //CODICE//

    int M=10000,N=100;
    int L=M/N;
    double x,r;
    double sum=0.;
    double a=0,b=1;

    vector<double>supp(N);     //vector per il primo metodo
    vector<double>supp2(N);
    vector<double>mean(N);
    vector<double>mean2(N);

    vector<double>help(N);      //vector per il secondo metodo
    vector<double>help2(N);
    vector<double>medie(N);
    vector<double>medie2(N);

    vector<double>err(N);
    vector<double>err2(N);

    ofstream out;
    out.open("dati.csv");

    //primo metodo

    for(int j=0;j<N;j++){
        for(int i=0;i<L;i++){
            x=rnd.Rannyu(a,b);
            sum+=f(x);
        }
        supp[j]=(b-a)*(sum/L);
        supp2[j]=pow(supp[j],2);
        mean[j]=accumulate(supp.begin(),supp.end(),0.)/(j+1);
        mean2[j]=accumulate(supp2.begin(),supp2.end(),0.)/(j+1);
        err[j]=StatisticError(mean,mean2,j);

        sum=0;
    }

    //secondo metodo//

    double pmax= 3./2.;

    sum=0;
    for(int j=0;j<N;j++){
        for(int i=0;i<L;i++){
            do{
            r=rnd.Rannyu();
            x=rnd.Rannyu(a,b);
            } while(r>=p(x)/pmax);
            //cout<<p(x)<<endl;
            sum+=g(x);
        }
        help[j]=sum*(b-a)/double(L);
        cout<<help[j]<<endl;
        help2[j]=pow(help[j],2);
        medie[j]=accumulate(help.begin(),help.end(),0.)/(j+1);
        medie2[j]=accumulate(help2.begin(),help2.end(),0.)/(j+1);
        err2[j]=StatisticError(medie,medie2,j);

        out<<mean[j]<<","<<err[j]<<","<<medie[j]<<","<<err2[j]<<endl;
        sum=0;
    }
    out.close();

    return 0;
}