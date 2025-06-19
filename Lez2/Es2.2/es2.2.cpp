#include "random.h"
#include <numeric>
#include <cmath> // Aggiunto per M_PI e altre funzioni matematiche
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

double StatisticError(double avg, double avg2, int n) {
    if(n<=1) return 0;
    return sqrt(abs(avg2-pow(avg,2))/(n-1));
}


int main(){
    
    Random rnd;
    ifstream Primes("Primes");
    int seed[4];
    int p1,p2;
    if (Primes.is_open()){
       Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();
   
    ifstream input("seed.in");
    string property;
    if(input.is_open()){
        while(!input.eof() ){
            input >> property;
            if(property=="RANDOMSEED" ){
                input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
                rnd.SetRandom(seed,p1,p2);
            }
        } 
        input.close();
    } else cerr << "PROBLEM: Unable to open seed.in" << endl;

    //CODICE// 

    ofstream out;
    ofstream out2;
    ofstream out3;
    out.open("Unif.csv");
    out2.open("Solid.csv");
    out3.open("distanze.csv");
    int M=100,N=10000;
    double x=0,y=0,z=0,theta,phi,rand;
    double RWx=0;
    double RWy=0;
    double RWz=0;
    double a=1.;
    double p=0.5;
    double choose;
    vector<vector<double>>r1(N,(vector<double>(M+1,0.)));
    vector<vector<double>>r2(N,(vector<double>(M+1,0.)));
    
    vector<double>r(M+1);
    vector<double>r_quad(M+1); 
    vector<double>R(M+1);
    
    vector<double>rs(M+1);
    vector<double>rs_quad(M+1);
    vector<double>Rs(M+1);
    vector<double>err(M+1);
    vector<double>err2(M+1);
    double dist_sq;
    double sum_r2 = 0;   // Somma di |r_i|^2
    double sum_r4 = 0;   // Somma di (|r_i|^2)^2

/*===========================================
                CASO UNIFORME
============================================*/

    out<<0.<<","<<0.<<","<<0.<<endl;

    for(int j=0;j<N;j++){
        RWx=0;
        RWy=0;
        RWz=0;
        for(int i=1;i<=M;i++){ 
            x=0;
            y=0;
            z=0;
            rand=rnd.Rannyu();
            choose=floor(rnd.Rannyu(0,3))+1; 

            if(rand > p) {
                if(choose == 1) x=1;
                else if(choose==2) y=1;
                else if(choose==3) z=1;
            }
                
            if(choose == 1) RWx+=2*a*(x-0.5);
            if(choose == 2) RWy+=2*a*(y-0.5);
            if(choose == 3) RWz+=2*a*(z-0.5);
            
            if(j==0)out<<RWx<<","<<RWy<<","<<RWz<<endl;
            r1[j][i]=sqrt(pow(RWx,2)+pow(RWy,2)+pow(RWz,2));
        }
    }
    
    for(int i=0; i<=M; i++){
        sum_r2=0;   // Somma di |r_i|^2
        sum_r4=0;   // Somma di (|r_i|^2)^2
        for(int j=0; j<N; j++){
            dist_sq=pow(r1[j][i],2); // Distanza al quadrato per il blocco j al passo i
            sum_r2+=dist_sq;
            sum_r4+=pow(dist_sq,2);
        }
        r[i]=sum_r2/N;      // Media <|r_i|^2>
        r_quad[i]=sum_r4/N; // Media <(|r_i|^2)^2>
        R[i]=sqrt(r[i]); 
        err[i] = StatisticError(r[i], r_quad[i], N);            // Errore su <|r_i|^2>

        err[i]=err[i]/(2*R[i]);    //derivata di sqrt, altrimenti calcolerei solo l' errore su <|r_i|^2>
       
    }
    out.close();

/*===========================================
                CASO CONTINUO
============================================*/

    for(int j=0;j<N;j++){
        RWx=0;
        RWy=0;
        RWz=0;
        for(int i=1;i<=M;i++){
            phi=rnd.Rannyu(0,2*M_PI);
            theta=rnd.SolidAngle(); 

            x=a*cos(phi)*sin(theta);
            y=a*sin(phi)*sin(theta);
            z=a*cos(theta);  

            RWx+=x;
            RWy+=y;
            RWz+=z;

            r2[j][i]=sqrt(pow(RWx,2)+pow(RWy,2)+pow(RWz,2));
            if(j==0)out2<<RWx<<","<<RWy<<","<<RWz<<endl;
        }
    }
    
    for(int i=0; i<=M; i++){
        sum_r2 = 0;
        sum_r4 = 0;
        for(int j=0; j<N; j++){
            dist_sq=pow(r2[j][i], 2);
            sum_r2+=dist_sq;
            sum_r4+=pow(dist_sq,2);
        }
        rs[i]=sum_r2/N;
        rs_quad[i]=sum_r4/N;
        
        Rs[i]=sqrt(rs[i]);

        err2[i]=StatisticError(rs[i],rs_quad[i],N);
        err2[i]=err[i]/(2*Rs[i]);    //sempre per la propagazione dell' errore
        
        out3<<i<<","<<R[i]<<","<<err[i]<<","<<Rs[i]<<","<<err2[i]<<endl;
    }
    out2.close();
    out3.close();

    return 0;
}