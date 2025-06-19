#include <iostream>
#include "system.h"

using namespace std;

int main (int argc, char *argv[]){

  int nconf = 1;
  System SYS;
  SYS.initialize();
  SYS.initialize_properties();
  SYS.block_reset(0);
  int n=10000;
  int N=SYS.get_nbl();
  int L=SYS.get_nsteps();
  int M=N*L;
  
  /*
  for(int i=0;i<n;i++){   //EQUILIBRAZIONE DEL SISTEMA//
    SYS.step();
  }

  ofstream out;
  out.open("../OUTPUT/AutoCorrMC.dat");

  for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
      SYS.step();
      SYS.measure();
    }
    SYS.averages(i+1);
    SYS.block_reset(i+1);
    if((i+1)%10000==0) cout<<"Blocco "<<i+1<<"/"<<SYS.get_nbl()<<endl;
  }*/

  /*==========================================
               METROPOLIS AUTOCORR
  ===========================================*/

  /*vector<double> X(SYS.get_nbl());   //vector per l' autocorrelazione//

  for(int j=0;j<SYS.get_nbl();j++){
    SYS.AutoCorrelation(SYS.get_nbl(),j,X);
    
    out<<X[j]<<endl;
  }
  out.close();*/

  /*===========================================
               METROPOLIS ERROR (L)
  ===========================================*/

 /* ofstream out2;
  out2.open("../OUTPUT/ErroriMC.dat");
  double err;
  vector<int>L_={100,200,400,600,800,1000,1500,2000,2500,3000,3500,4000,4500,5000};
  for(int i=0;i<14;i++){
    N=M/L_[i];
    err=SYS.StatisticUncertainties(L_[i],N);
    out2<<err<<endl;
    cout<<"L = "<<L_[i]<<" Completato"<<endl;
    
  }
  SYS.finalize();
  out2.close();*/

  /*===========================================
              METROPOLIS GAS SIMULATION 
  ===========================================*/

  /*nconf = 1;
  System SYS2;
  SYS2.initialize();
  SYS2.initialize_properties();
  SYS2.block_reset(0);
  n=10000;
  N=SYS2.get_nbl();
  L=SYS2.get_nsteps();
  M=N*L;

  for(int i=0;i<n;i++){   //EQUILIBRAZIONE DEL SISTEMA//
    SYS2.step();
  }

  for(int i=0; i < SYS2.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS2.get_nsteps(); j++){ //loop over steps in a block
      SYS2.step();
      SYS2.measure();
    }
    SYS2.averages(i+1);
    SYS2.block_reset(i+1);
    //cout<<"Blocco "<<i+1<<"/"<<SYS2.get_nbl()<<endl;
  }*/




  /*==========================================
          MOLECULAR DYNAMICS AUTOCORR
  ===========================================*/

  ofstream out;
  out.open("../OUTPUT/AutoCorrMD.dat");
  nconf = 1;
  System SYS3;
  SYS3.initialize();
  SYS3.initialize_properties();
  SYS3.block_reset(0);
  n=10000;
  N=SYS3.get_nbl();
  L=SYS3.get_nsteps();
  M=N*L;

  for(int i=0;i<n;i++){   //EQUILIBRAZIONE DEL SISTEMA//
    SYS3.step();
  }

  for(int i=0; i < SYS3.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS3.get_nsteps(); j++){ //loop over steps in a block
      SYS3.step();
      SYS3.measure();
    }
    SYS3.averages(i+1);
    SYS3.block_reset(i+1);
    if((i+1)%10000==0) cout<<"Blocco "<<i+1<<"/"<<SYS3.get_nbl()<<endl;
  }

  vector<double> X(SYS3.get_nbl());   //vector per l' autocorrelazione//

  for(int j=0;j<SYS3.get_nbl();j++){
    SYS3.AutoCorrelation(SYS3.get_nbl(),j,X);
    
    out<<X[j]<<endl;
  }
  out.close();

  /*==========================================
          MOLECULAR DYNAMICS ERROR
  ===========================================*/

  ofstream out2;
  out2.open("../OUTPUT/ErroriMD.dat");
  double err;
  vector<int>L_={100,200,400,600,800,1000,1500,2000,2500,3000,3500,4000,4500,5000};
  for(int i=0;i<14;i++){
    N=M/L_[i];
    err=SYS3.StatisticUncertainties(L_[i],N);
    out2<<err<<endl;
    cout<<"L = "<<L_[i]<<" Completato"<<endl;
    
  }
  SYS3.finalize();
  out2.close();


  /*===========================================
        MOLECOLAR DYNAMICS GAS SIMULATION 
  ===========================================*/

  /*nconf = 1;
  System SYS2;
  SYS2.initialize();
  SYS2.initialize_properties();
  SYS2.block_reset(0);
  n=10000;
  N=SYS2.get_nbl();
  L=SYS2.get_nsteps();
  M=N*L;

  for(int i=0;i<n;i++){   //EQUILIBRAZIONE DEL SISTEMA//
    SYS2.step();
  }

  for(int i=0; i < SYS2.get_nbl(); i++){ //loop over blocks
    for(int j=0; j < SYS2.get_nsteps(); j++){ //loop over steps in a block
      SYS2.step();
      SYS2.measure();
    }
    SYS2.averages(i+1);
    SYS2.block_reset(i+1);
    if((i+1)%100==0) cout<<"Blocco "<<i+1<<"/"<<SYS2.get_nbl()<<endl;
  }*/


  return 0;
}
