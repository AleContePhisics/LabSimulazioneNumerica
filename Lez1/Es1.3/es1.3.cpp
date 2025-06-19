#include"random.h"
#include <numeric>
#include <cmath>

int main(){

    Random rnd;

    //GENERATORE NUMERI CASUALI//

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

    double d=1.;
    double L=0.5;  
    unsigned int counter=0;
    int M=100000;  //# lanci totali effettuabili
    int N=100;     //# blocchi per la statistica
    int K=1;       //# ripetizioni esperimento
    double sum=0;
    vector<double>pig(N);
    vector<double>pig2(N);
    vector<double>r1(2);  //vector punto 1
    vector<double>r2(2);  //vector punto 2
    vector<double>choise(2);
    vector<double>meanpi(N);  //medie A_i
    vector<double>meanpi2(N); //medie (A_i)^2
    vector<double>err(N); 
    double theta;

    ofstream out;
    out.open("dati3.csv");

    for(int j=0;j<N;j++){
        for(int k=0;k<K;k++){
            for(int i=0;i<M/N;i++){
                r1[0]=rnd.Rannyu(0,d);  //x primo punto
                r1[1]=rnd.Rannyu(0,d);  //y primo punto

                do{
                choise[0]=rnd.Rannyu(-L,L);  //scelta punto sull' asse x della circ del punto 2
                choise[1]=rnd.Rannyu(-L,L);  //scelta punto sull' asse y della circ del punto 2
                }while(pow(choise[0],2)+pow(choise[1],2)>pow(L,2));//rigetta se i punti sono fuori dalla circ di raggio L
            
                theta=atan2(choise[1],choise[0]);  //angolo tra y e x calcolati
            
                r2[0]=r1[0]+L*cos(theta);  //x punto 2
                r2[1]=r1[1]+L*sin(theta);  //y punto 2
            
                if(r2[1]>=d || r2[1]<=0 || r1[1]==d || r1[1]==0){counter++;}
         
            }
            sum+=(2*L*M)/(N*d*counter);  //calcolo pigreco per un blocco con K esperimenti
            counter=0;
            
        }
        pig[j]=sum/K;
        pig2[j]=pow(pig[j],2);
        meanpi[j]=accumulate(pig.begin(),pig.end(),0.)/(j+1);
        meanpi2[j]=accumulate(pig2.begin(),pig2.end(),0.)/(j+1);
        err[j]=StatisticError(meanpi,meanpi2,j);
        
        out<<meanpi[j]<<","<<err[j]<<endl;
        sum=0;
    }
    
    return 0;
}