# include "GenAlgorithm.h"

int main(int argc, char** argv){

    if(argc!=2 || stoi(argv[1])>2 || stoi(argv[1])<0){
        cout<<"Input Error structure:<./simulator.exe><0=circle,1=rnd square,2=europe>"<<endl;
        exit(1);
    }
    unsigned int ex=stoi(argv[1]);
    ofstream kout;
    if(ex==0)kout.open("../OUTPUT/CircleLoss.dat");
    else kout.open("../OUTPUT/SquareLoss.dat");
    
    unsigned int M=200;                                             //number of path
    unsigned int N=34;                                              //number of cities
    unsigned int T=2000;                                            //number of new generation
    if(ex==2)N=39;
    Population Popul(M,N);
    Popul.Initialization();
    Popul.CitiesConfig(ex);
    Popul.OrderChromo();
    double pc=0.8;   
    double pm1,pm2,pm3,pm4;

    if(ex==0)pm1=0.5;pm2=0.15;pm3=0.15,pm4=0.15;    //perfetto

    if(ex==1)pm1=0.4,pm2=0.1,pm3=0.1,pm4=0.1;   //buono (5.73)

    if(ex==2)pm1=0.3;pm2=0.1;pm3=0.1,pm4=0.1;    //medio (100 e qualcosa di errore,2922)

    double Fit;
    double AvgFit;
    double sum=0;

    //inizio algoritmo//

    for(int i=0;i<T;i++){
        
        Fit=Popul.L(0);
        for(int j=0;j<M/2;j++){
            sum+=Popul.L(j);
        }
        AvgFit=2*sum/double(M);
        kout<<Fit<<","<<AvgFit<<endl;
        cout<<Fit<<endl;
        Popul.NewGeneration(pc,pm1,pm2,pm3,pm4);
        Popul.OrderChromo();
        sum=0;
    }
    Popul.ChromoShow();
    Popul.GetBestPath(ex);
    kout.close();

    return 0;
}