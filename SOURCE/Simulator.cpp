#include "GenAlgorithm.h"
#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Inizializza MPI

    if(argc != 2 || stoi(argv[1]) > 3 || stoi(argv[1]) < 0){
        cout << "Input Error structure:<./simulator.exe><0=circle,1=rnd square,2=europe,3=italy>"<<endl;
        MPI_Abort(MPI_COMM_WORLD, 1); // esci con errore per tutti i processi
    }

    int ex = stoi(argv[1]);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID processo corrente
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Numero totale di processi

    string filename;

    if(ex==0)filename = "../OUTPUT/CircleLoss" + to_string(rank) + ".dat";
    else if(ex==1)filename = "../OUTPUT/SquareLoss" + to_string(rank) + ".dat";
    else if(ex==2)filename = "../OUTPUT/EuropeLoss" + to_string(rank) + ".dat";
    else if(ex==3)filename = "../OUTPUT/ItalyLoss" + to_string(rank) + ".dat";

    string loss_filename;

    if(ex==0)loss_filename = "../OUTPUT/CircleLossRank" + to_string(rank) + ".dat";
    if(ex==1)loss_filename = "../OUTPUT/SquareLossRank" + to_string(rank) + ".dat";
    if(ex==2)loss_filename = "../OUTPUT/EuropeLossRank" + to_string(rank) + ".dat";
    if(ex==3)loss_filename = "../OUTPUT/ItalyLossRank" + to_string(rank) + ".dat";

    ofstream kout(loss_filename);
    if (!kout.is_open()) {
        cerr << "[Rank " << rank << "] Errore apertura file loss!" << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    unsigned int M = 200;      // numero di cammini
    unsigned int N = 34;       // numero di città
    unsigned int G = 2000;     // numero di generazioni
    if (ex == 2) N = 39;
    if (ex == 3) N = 110;
    unsigned int T = 100;      // numero di nuove generazioni prima di una migrazione

    Population Popul(M, N);
    Popul.Initialization();
    Popul.CitiesConfig(ex,rank);
    Popul.OrderChromo();

    double pc=0.80;
    double pm1,pm2,pm3,pm4;

    if(ex==0)pm1=0.5;pm2=0.1;pm3=0.05,pm4=0.05;    //perfetto (6.24)

    if(ex==1)pm1=0.2,pm2=0.05,pm3=0.05,pm4=0.1;   //forse il secondo migliore (5.28)

    if(ex==2)pm1=0.3;pm2=0.1;pm3=0.15,pm4=0.10;    //molto buono (2822)

    if(ex==3)pm1=0.5;pm2=0.15;pm3=0.15;pm4=0.15;    // medio buona (88.27)

    double Fit,AvgFit,sum=0.;
    vector<unsigned int> colombo={0,1,2,3,4,5,6,7,8,9};      // continente che verrà conquistato
    vector<int> pairing(size,-1);
    for (int i=0;i<size;i+=2) {
        int a=colombo[i];
        int b=colombo[i+1];
        pairing[a]=b;
        pairing[b]=a;
    }

    /*==========================//
              ALGORITMO
    ============================*/

    for(int i=0;i<G;i++){
        Fit=Popul.L(0);
        for(int j=0;j<M/2;j++){
            sum+=Popul.L(j);
        }
        AvgFit=2*sum/double(M);
        kout<<Fit<<","<<AvgFit<<endl;

        Popul.NewGeneration(pc,pm1,pm2,pm3,pm4);
        Popul.OrderChromo();
        sum=0;

        if(i%T==0){
            if(rank==0)rotate(colombo.begin(),colombo.end()-1,colombo.end());
            for (int i=0;i<size;i+=2) {
                int a=colombo[i];
                int b=colombo[i+1];
                pairing[a]=b;
                pairing[b]=a;
            }
            MPI_Bcast(pairing.data(), size, MPI_INT, 0, MPI_COMM_WORLD);
            ScambioBestChromosome(Popul,rank,size,pairing,M);
        }

    }
    Popul.OrderChromo();
    Popul.GetBestPath(ex,rank);
    kout.close();

    MPI_Finalize();  // Termina MPI
    return 0;
}
