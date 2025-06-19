# include "GenAlgorithm.h"
# include <iomanip>
# include <unordered_set>

double Dist(double x1,double y1,double x2,double y2){
    double L;
    if(x1==x2 & y1==y2)L=0;
    L=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    return L;
}

void Chromosome :: SingleChromoShow(){
    for(int i=0;i<n_genes;i++){
        cout<<GetGene(i)<<endl;
    }
}

unsigned int Chromosome :: GetGene(unsigned int i){
    if(i<n_genes)return Chromo[i];
    else if(i==n_genes) return Chromo[0];
    else {cerr<<"Error gene out of bounds, gene ="<<i<<endl;
        exit(1);
    }
}

void Chromosome :: Check() {
    if (Chromo[0]!=1) {
        cerr<<"Error: Initial gene is not 1."<<endl;
        exit(1);
    }
    unordered_set<unsigned int> seen;
    for (unsigned int gene:Chromo) {
        if (!seen.insert(gene).second) {
            cerr<<"Error: Duplicate gene found"<<endl;
            exit(1);
        }
    }
}

void Chromosome :: Permutation(Random& rnd){
    unsigned int r1=rnd.RandInt(1,n_genes-1);
    unsigned int r2=rnd.RandInt(1,n_genes-1);

    if(r1==r2) return;
    double x;
    x=GetGene(r1);
    SetGene(GetGene(r2),r1);
    SetGene(x,r2);
    Check();
                                      
}

void Chromosome :: Shift(Random& rnd){
    rotate(Chromo.begin()+1,Chromo.end()-1,Chromo.end());
    Check();
}

Population::Population(unsigned int m,unsigned int n){     //set the dimension of chromo(path) and genes(cities)
    Popul.resize(m);
    n_chromo=m;
    n_genes=n;
    for(int i=0;i<n_chromo;i++){
        Popul[i]=Chromosome(n);
    }
    M.set_size(n_genes,n_genes);
};

void Chromosome :: Contamination(unsigned int i,Random& rnd){
    unsigned int r;
    do{
        r=rnd.RandInt(1+i,n_genes-i-1);
    }while(r%2!=0);
    //cout<<"r="<<r<<endl;
    for(int j=0;j<i;j++){
        swap(Chromo[r-(i-j)],Chromo[r+j+1]);
    }
    Check();
}

void Population :: Initialization(){
    int p1, p2; 
    ifstream Primes("../INPUT/Primes");
    Primes >> p1 >> p2 ;
    Primes.close();
    int seed[4]; 
    ifstream Seed("../INPUT/seed.in");
    Seed >> seed[0] >> seed[1] >> seed[2] >> seed[3];
    rnd.SetRandom(seed,p1,p2);


    for(int i=0;i<n_genes;i++){                             //set the first chromo to be 1,2,3,...,33,34
        Popul[0].SetGene(i+1,i);
    }
    for(int i=1;i<n_chromo;i++){                            //set all of chromos to be like the first one 
        Popul[i]=Popul[0];
    }
    for(int i=1;i<n_chromo;i++){                            //shuffle all of n_chromo-1 
        for(int j=0;j<1000;j++){
            Popul[i].Permutation(rnd);
            Popul[i].Check();
        }
    }
}

void Population :: ChromoShow(){                            //show all genes of all chromos
    for(int i=0;i<n_chromo;i++){
        if(i<9) cout<<"Chromo "<<i+1<<":    ";
        else if(i<99 & i>=9) cout<<"Chromo "<<i+1<<":   ";
        else cout<<"Chromo "<<i+1<<":  ";
        for(int j=0;j<n_genes;j++){
            cout << setw(3) << Popul[i].GetGene(j);
        }
        cout<<endl;
    }
}

void Population :: CitiesConfig(unsigned int k){ 
    double theta;
    vector<double>xcity(n_genes);
    vector<double>ycity(n_genes);
    ofstream out;
    out.open("../OUTPUT/Circle.dat");
    ofstream out2;
    out2.open("../OUTPUT/Square.dat");
    
    if(k==0){    
        for(int i=0;i<n_genes;i++){                         // cities around a circle r=1
            theta=2*M_PI*rnd.Rannyu();
            xcity[i]=cos(theta);
            ycity[i]=sin(theta);
        
            out<<xcity[i]<<","<<ycity[i]<<endl;
        }
        for(int i=0;i<n_genes;i++){ 
            for(int j=0;j<n_genes;j++){
                M(i,j)=Dist(xcity[i],ycity[i],xcity[j],ycity[j]);
            }
        }
        out<<xcity[0]<<","<<ycity[0]<<endl;
    }
    else if(k==1){
        for(int i=0;i<n_genes;i++){                         // random cities in a l=1 square
            xcity[i]=rnd.Rannyu();
            ycity[i]=rnd.Rannyu();
            
            out2<<xcity[i]<<","<<ycity[i]<<endl;
        }
        for(int i=0;i<n_genes;i++){
            for(int j=0;j<n_genes;j++){
                M(i,j)=Dist(xcity[i],ycity[i],xcity[j],ycity[j]);
            }
        }
        out2<<xcity[0]<<","<<ycity[0]<<endl;
    }

    else if(k==2){
        ifstream in;
        in.open("../INPUT/europa.dat");
        for(int i=0;i<n_genes;i++){
            in>>xcity[i]>>ycity[i];
        }
        for(int i=0;i<n_genes;i++){
            for(int j=0;j<n_genes;j++){
                M(i,j)=Dist(xcity[i],ycity[i],xcity[j],ycity[j]);
            }
        }
        in.close();
    }
    else{ 
        cout<<"Error Simulation"<<endl;
        exit(1);
    }
    out.close();
    out2.close();
}

void Population :: LossShow(){
    for(int i=0;i<n_genes;i++){
        for(int j=0;j<n_genes;j++){
            cout<<fixed<<setprecision(1)<<M(i,j)<<setw(4);
        }
        cout<<endl;
    }
}

void Population :: SetChromo(Chromosome c,unsigned int i){
    for (int j=0;j<n_genes;j++){
        Popul[i].SetGene(c.GetGene(j),j);
    }
}

void Population :: LossChromoShow(){
    for(int i=0;i<n_chromo;i++){
        if(i<9) cout<<"Chromo "<<i+1<<":    ";
        else if(i<99 & i>=9) cout<<"Chromo "<<i+1<<":   ";
        else cout<<"Chromo "<<i+1<<":  ";
        cout<<L(i)<<endl;
    }
}

double Population :: L(unsigned int i){
    double L=0;
    unsigned int k,m;
    for(int j=0;j<n_genes;j++){
        k=Popul[i].GetGene(j);
        m=Popul[i].GetGene(j+1);
        L+=M(k-1,m-1);   //-1 dato che i geni vanno da 1 a 34 e gli indici di mat da 0 a 33
    }
    return L;
}

vector<Chromosome> Population :: Crossover(Chromosome c1, Chromosome c2) {
    vector<Chromosome>C(2);
    int r=rnd.RandInt(1,n_genes-1);
    Chromosome s1(n_genes);
    Chromosome s2(n_genes);
    vector<bool>index1(n_genes,false);
    vector<bool>index2(n_genes,false);
    unsigned int g1;
    unsigned int g2;

    // Copia la parte iniziale dei genitori nei figli
    for(int i=0;i<r;i++) {
        g1=c1.GetGene(i);
        g2=c2.GetGene(i);

        s1.SetGene(g1, i);
        s2.SetGene(g2, i);

        index1[g1]=true;
        index2[g2]=true;
    }

    // Completa s1 con i geni di c2 non ancora usati
    int idx1 = r, idx2 = r;
    for(int i=0;i<n_genes&&(idx1<n_genes||idx2<n_genes);i++) {
        unsigned int g_from_c2 = c2.GetGene(i);
        unsigned int g_from_c1 = c1.GetGene(i);

        if (idx1 < n_genes && !index1[g_from_c2]) {
            s1.SetGene(g_from_c2, idx1++);
            index1[g_from_c2] = true;
        }

        if (idx2 < n_genes && !index2[g_from_c1]) {
            s2.SetGene(g_from_c1, idx2++);
            index2[g_from_c1] = true;
        }
    }
    s1.Check();
    s2.Check();
    C[0]=s1;
    C[1]=s2;
    return C;
}

void Chromosome::Inversion(Random& rnd) {
    unsigned int maxj=(n_genes-1)/2;
    unsigned int j=rnd.RandInt(1,maxj);
    unsigned int i=rnd.RandInt(j+1,n_genes-j);

    for (unsigned int k=0;k<j;k++) {
        swap(Chromo[i-j+k],Chromo[i+k]);
    }
    Check();
}



void Population :: OrderChromo(){
    vec Loss(n_chromo);
    uvec Index(n_chromo);
    vector<Chromosome>v(n_chromo);
    for(int i=0;i<n_chromo;i++){
        Loss[i]=L(i);
    }
    Index=sort_index(Loss);  //riordina in base alle loss salvando solo l' indice
    for(int i=0;i<n_chromo;i++){
        v[i]=Popul[Index[i]];
        v[i].Check();
    } 
    Popul=v;
}

unsigned int Population :: Selection(){
    double r=rnd.Rannyu();
    double p=4;
    unsigned int j=floor(n_genes*pow(r,p))+1;
    return j;
}

void Population :: NewGeneration(double pc,double pm1,double pm2,double pm3,double pm4){
    unsigned int m,n;
    double sum=0;
    double r;
    vector<Chromosome>C(n_chromo);
    vector<Chromosome>Help(2);
    for(int i=0;i<n_chromo;i+=2){
        m=Selection();
        n=Selection();
        r=rnd.Rannyu();
        if(r<pc){
            Help=Crossover(Popul[m],Popul[n]);
            C[i]=Help[0];
            C[i+1]=Help[1];
        }
        else{
            C[i]=Popul[m];
            C[i+1]=Popul[n];   
        }
        r=rnd.Rannyu();
        
        if(r<pm1){
            C[i].Permutation(rnd);
            C[i+1].Permutation(rnd);      
        }
        r=rnd.Rannyu();
        if(r<pm2){
            C[i].Shift(rnd);
            C[i+1].Shift(rnd);      
        }
        r=rnd.Rannyu();
        //int f=rnd.RandInt(5,8);
        int f=6;    //6 per square
        if(r<pm3){
            C[i].Contamination(f,rnd);
        }
        r=rnd.Rannyu();
        if(r<pm4){
            C[i].Inversion(rnd);
        }
        
    }
    for(int i=0;i<n_chromo;i++){
        SetChromo(C[i],i);
    }
}

void Population :: GetBestPath(unsigned int ex){

    if(ex==0){
        ofstream out;
        out.open("../OUTPUT/CirclePath.dat");
        for(int i=0;i<n_genes;i++){
            out<<Popul[i].GetGene(i)<<endl;
        }
        out.close();
    }
    else if(ex==1){
        ofstream out2;
        out2.open("../OUTPUT/SquarePath.dat");
        for(int i=0;i<n_genes;i++){
            out2<<Popul[i].GetGene(i)<<endl;
        }
        out2.close();

    }
    else if(ex==2){
        ofstream out3;
        out3.open("../OUTPUT/EuropePath.dat");
        for(int i=0;i<n_genes;i++){
            out3<<Popul[i].GetGene(i)<<endl;
        }
        out3.close();

    }
}




