# include "system.h"
# include <iomanip>

using namespace std;

int main(){

    ofstream out;
    out.open("../OUTPUT/Risultati.dat",ios::app);
    ofstream out2;
    out2.open("../OUTPUT/Mu.dat",ios::app);
    ofstream out3;
    out3.open("../OUTPUT/Sigma.dat",ios::app);
    ofstream out4;
    out4.open("../OUTPUT/BestH.dat",ios::app);
    ofstream out5;
    out5.open("../OUTPUT/ModuleSquare.dat",ios::app);

    System Sys;
    double accept=0.;
    Sys.initialize();
    double delta1,delta2;
    double mu=1.5,mu_=1.5;
    double sigma=1,sigma_=1;
    double x0=0.3;
    double T=1.5,r;
    Hamiltonian H(mu,sigma);
    Hamiltonian h(mu_,sigma_);
    H.SetMean(Sys.Hm(mu,sigma,x0));
    double p,err;
    int M=300,P=20;
    vector<double>sum(M*P);
    vector<double>sum2(M*P);
    vector<double>Avg(M*P);
    vector<double>Avg2(M*P);
    
    for(int i=0;i<M;i++){
        mu=H.GetMu();
        sigma=H.GetSigma();

        for(int j=0;j<P;j++){
            do{
                delta1=Sys.delta();
                delta2=Sys.delta();
                mu_=mu+delta1;
                sigma_=sigma+delta2;

            } while (mu_<0 || sigma_<0);
            h.SetSigma(sigma_);
            h.SetMu(mu_);
            h.SetMean(Sys.Hm(mu_,sigma_,x0));

            if(h.GetMean()>H.GetMean()) p=exp(-(h.GetMean()-H.GetMean())/T);
            else p=1;

            r=Sys.Uniform();

            if(r<p){
                Sys.Swap(H,h);
                mu=mu_;
                sigma=sigma_;
            }
            sum[i]=H.GetMean();
            sum2[i]=pow(H.GetMean(),2);
            out<<H.GetMean()<<endl;
            out2<<H.GetMu()<<endl;
            out3<<H.GetSigma()<<endl;
            }
            accept=0;
            T *= 0.95;

            cout<<i+1<<"/"<<M<<endl;
        }
    out2.close();
    out3.close();

    for(int i=0;i<M*P;i++){
        Avg[i]=accumulate(sum.begin(),sum.begin()+i,0.)/(i+1);
        Avg2[i]=accumulate(sum2.begin(),sum2.begin()+i,0.)/(i+1);
        err=StatisticError(Avg[i],Avg2[i],i);
        out<<err<<endl;
    }
    out.close();

    //seconda parte//

    x0=0.3;
    mu=H.GetMu();
    sigma=H.GetSigma();

    int L=5000;
    sum.clear();
    sum.resize(L);
    sum2.clear();
    sum2.resize(L);
    Avg.clear();
    Avg.resize(L);
    Avg2.clear();
    Avg2.resize(L);

    //energia con mu e sigma corretti//

    for(int i=0;i<L;i++){
        sum[i]=Sys.Hm(mu,sigma,x0);
        sum2[i]=pow(sum[i],2);
    }
    for(int i=0;i<L;i++){
        Avg[i]=accumulate(sum.begin(),sum.begin()+i,0.)/(i+1);
        Avg2[i]=accumulate(sum2.begin(),sum2.begin()+i,0.)/(1+i);
        err=StatisticError(Avg[i],Avg2[i],i);
        out4<<Avg[i]<<","<<err<<endl;
    }

    //prob. modulo quadro//

    L=100000;
    vector<double>Module(L);
    double xmin=-3,xmax=3;
    unsigned int bin;
    int n_bins=100;
    double bin_size=(xmax-xmin)/n_bins;
    for(int i=0;i<L;i++){
        x0=Sys.Metro(mu,sigma,x0);
        bin=int((x0-xmin)/bin_size);
        Module[bin]++;
    }
    for(int i=0;i<n_bins;i++){
        out5<<Module[i]<<endl;
    }


    out4.close();
    out5.close();
    return 0;
}