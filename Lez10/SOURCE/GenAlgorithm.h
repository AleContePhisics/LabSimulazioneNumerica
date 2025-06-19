#ifndef __GenAlgorithm__
#define __GenAlgorithm__

# include "random.h"
# include <iostream>
# include <mpi.h>
# include <armadillo>

using namespace std;
using namespace arma;

class Chromosome {
    public:

    Chromosome():n_genes(0){Chromo.clear();}
    Chromosome(unsigned int n):n_genes(n){Chromo.resize(n, 0);}
    Chromosome(initializer_list<unsigned int> list) {
        n_genes = list.size();
        Chromo = list;
    }
    vector<unsigned int>ToVector()const{return Chromo;}
    void FromVector(const vector<unsigned int>&v){
        Chromo=v;
        n_genes=v.size();
    }
    int GetSize(){return Chromo.size();}
    void SetGene(unsigned int x,unsigned int i){Chromo[i]=x;}
    void Check();                                                // check if the first gene is 1 and all of genes are different
    void Permutation(Random&);                                   // swap two genes of chromo
    void Shift(Random&);                                         // shift all of n_genes-1 to the right
    unsigned int GetGene(unsigned int i);
    void SingleChromoShow();
    void Contamination(unsigned int i,Random&);
    void Inversion(Random&);

    protected:

    unsigned int n_genes;
    vector<unsigned int> Chromo;
};

class Population{
    public:
    
    Population(unsigned int m,unsigned int n);

    Random rnd;
    void Initialization();                                       // generate the first configuration of chromosomes
    void ChromoShow();                                           // show all genes of all chromosomes
    void LossShow();                                             // show the loss of two genes
    void LossChromoShow();                                       // show the loss of a chromosome
    Chromosome GetChromo(unsigned int k){return Popul[k];}       // show all genes of a single chromosome
    void SetChromo(Chromosome C,unsigned int i);                 // change a chromosome in to another
    vector<Chromosome> Crossover(Chromosome,Chromosome);         // mix the genes of two chromosomes
    void CitiesConfig(unsigned int,int);                           // set the values of distances
    double L(unsigned int i);                                    // get the loss function of chromosome
    void OrderChromo();                                          // order the population with the lower Loss 
    unsigned int Selection();                                    // choose one chromo by looking L
    void NewGeneration(double,double,double,double,double);      // create the new population after sex and mutation
    void GetBestPath(unsigned int,int);                          // get the chromosome with best L of a single generation

    protected:

    vector<Chromosome> Popul;
    unsigned int n_chromo;                                       // number of chromosome
    unsigned int n_genes;                                        // number of genes(cities)
    mat M;                                                       // matrix of all distance about cities
};

double Dist(double x1,double y1,double x2,double y2);            // distance function

void ScambioBestChromosome(Population& Popul, int rank, int size, std::vector<int>& pairing, int M);


#endif