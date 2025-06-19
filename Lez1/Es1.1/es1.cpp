#include"random.h"
#include<numeric>

int main(){
    Random rnd;
    int M=100000;
    int N=100;
    int L=M/N;
    vector<double>random(M);
    vector<double>sum(N);
    vector<double>sum2(N);
    vector<double>sum3(N);
    vector<double>sum4(N);
    vector<double>medie(N);
    vector<double>medie2(N);
    vector<double>var(N);
    vector<double>var2(N);
    vector<double>err(N);
    vector<double>err2(N);
    ofstream file("dati.csv");
  
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

    /*========================================
              CODICE DI CALCOLO
    =========================================*/

    //genero i numeri e li inserisco in un vector//

    for(int i=0;i<M; i++){
        random[i]=rnd.Rannyu();
    }

    //calcolo la differenza <r> dei numeri per k blocchi e <(r-1/2)^2> con k=1,2,..,N //
    int p;
    for(int i=0;i<N;i++){
        for(int j=0;j<L;j++){
            p=j+i*L;
            sum[i]+=random[p];
            sum3[i]+=pow(random[p]-0.5,2);
        }
        sum[i]=sum[i]/L;
        sum2[i]=pow(sum[i],2);
        sum3[i]=sum3[i]/L;
        sum4[i]=pow(sum3[i],2);
        
    }

    for(int k=1;k<=N;k++){
        for(int i=0;i<k;i++){
            medie[k-1]+=sum[i];
            medie2[k-1]+=sum2[i];
            var[k-1]+=sum3[i];
            var2[k-1]+=sum4[i];

        }
        medie[k-1]=medie[k-1]/k;
        medie2[k-1]=medie2[k-1]/k;
        err[k-1]=sqrt((medie2[k-1]-pow(medie[k-1],2))/k);

        var[k-1]=var[k-1]/k;
        var2[k-1]=var2[k-1]/k;
        err2[k-1]=sqrt((var2[k-1]-pow(var[k-1],2))/k);
    }

    rnd.SaveSeed();
    

    //CHI QUADRO TEST//

    M=100;
    int n=10000;
    vector<int>n_i(M,0);
    double r;
    vector<double>chi(M);
    vector<double> chi2(M);

    for(int i=0;i<M;i++){
        for(int j=0;j<n;j++){
            r=rnd.Rannyu();
            r=int(r*M);
            n_i[r]++;
        }
        for(int k=0;k<M;k++){
            chi2[k]=pow(n_i[k]-n/M,2)/(n/M);
        }
        chi[i]=accumulate(chi2.begin(),chi2.end(),0.);        
        fill(n_i.begin(),n_i.end(),0.);
        fill(chi2.begin(),chi2.end(),0.);
    }

    //Passaggio dati a file dati.csv//

    for(int i=0;i<N;i++){
        file<<medie[i]<<","<<err[i]<<","<<var[i]<<","<<err2[i]<<","<<chi[i]<<endl;
    }
    file.close();


    return 0;
}