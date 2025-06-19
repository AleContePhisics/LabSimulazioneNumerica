#include <iostream>
#include "system.h"

using namespace std;

int main (int argc, char *argv[]){

  System SYS;

  //H=0

  for(int j=0;j<=15;j++){    //Metropolis
    int nconf = 1;
    SYS.initialize();
    SYS.SetTemp(j*0.1);
    SYS.initialize_properties();
    SYS.block_reset(0);

    for(int i=0;i<SYS.get_nsteps()/2.;i++){     //Equilibrazione del Sistema
      SYS.step();
    }
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
      for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
      }
      SYS.averages(i+1);
      SYS.block_reset(i+1);
      cout<<"Blocco "<<i+1<<endl;
    }
    SYS.finalize();
    SYS.Reset();
  }

  for(int j=0;j<=15;j++){   //Gibbs
    SYS.initialize();
    SYS.SetSymType(3);
    SYS.SetTemp(j*0.1);
    SYS.initialize_properties();
    SYS.block_reset(0);

    for(int i=0;i<SYS.get_nsteps()/2.;i++){     //Equilibrazione del Sistema
      SYS.step();
    }
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
      for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
      }
      SYS.averages(i+1);
      SYS.block_reset(i+1);
      cout<<"Blocco "<<i+1<<endl;
    }
    SYS.finalize();
    SYS.Reset();

  }

  //H=0.02//

  for(int j=0;j<=15;j++){    //Metropolis

    SYS.initialize();
    SYS.SetSymType(2);
    SYS.SetTemp(j*0.1);
    SYS.SetH(0.02);
    SYS.initialize_properties();
    SYS.block_reset(0);

    for(int i=0;i<SYS.get_nsteps()/2.;i++){     //Equilibrazione del Sistema
      SYS.step();
    }
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
      for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
      }
      SYS.averages(i+1);
      SYS.block_reset(i+1);
      cout<<"Blocco "<<i+1<<endl;
    }
    SYS.finalize();
    SYS.Reset();

  }

  for(int j=0;j<=15;j++){   //Gibbs
    SYS.initialize();
    SYS.SetSymType(3);
    SYS.SetTemp(j*0.1);
    SYS.SetH(0.02);
    SYS.initialize_properties();
    SYS.block_reset(0);

    for(int i=0;i<SYS.get_nsteps()/2.;i++){     //Equilibrazione del Sistema
      SYS.step();
    }
    for(int i=0; i < SYS.get_nbl(); i++){ //loop over blocks
      for(int j=0; j < SYS.get_nsteps(); j++){ //loop over steps in a block
        SYS.step();
        SYS.measure();
      }
      SYS.averages(i+1);
      SYS.block_reset(i+1);
      cout<<"Blocco "<<i+1<<endl;
    }
    SYS.finalize();
    SYS.Reset();

  }
  return 0;
}

