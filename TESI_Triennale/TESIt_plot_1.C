#include<iostream>
#include<cmath>
#include<vector>
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
using namespace std;






void  TESIt_plot_1(){
//cominciamo cercando il barione xi, che ha una massa energetica di circa 1.3 GeV
//leggo il file dove ci sono i TTree
TFile* analisi=  new TFile("AnalysisResults_280234.root", "READ");
//
if(analisi->IsOpen()){
    cout<<"file aperto correttamente"<<endl;
}
//leggo il TTree
TDirectoryFile* dir1= (TDirectoryFile*) analisi->Get("PWGLF_StrVsMult");
TTree* tree= (TTree*) dir1->Get("fTreeCascade");
//bisogna capire quante Entries (righe) ci sono; 
int n= tree->GetEntries();
//
cout<<"Gli ingressi di tree sono "<<n<<endl;
//creo le variabili in cui metterò i dati del tree
float mass_V0=0; 
float mass_csi=0;
float mass_omega=0;
float mass_V0_lambda=0;
float mass_V0_alambda=0;
float DCA_casc=0;
float DCA_V0=0;

//
//Collego il Branch di mio interesse a questa variabile
tree->SetBranchAddress("fTreeCascVarV0Mass", &mass_V0);
tree->SetBranchAddress("fTreeCascVarMassAsXi", &mass_csi);
tree->SetBranchAddress("fTreeCascVarMassAsOmega", &mass_omega);
tree->SetBranchAddress("fTreeCascVarV0MassLambda", &mass_V0_lambda);
tree->SetBranchAddress("fTreeCascVarV0MassAntiLambda", &mass_V0_alambda);
tree->SetBranchAddress("fTreeCascVarDCACascDaughters", &DCA_casc);
tree->SetBranchAddress("fTreeCascVarDCAV0Daughters", &DCA_V0);
//
//costruiamo il TCanvas dove vediamo le masse SENZA APPLICARE IL DCA
//
TCanvas* c1= new TCanvas("c1", "masse SENZA TAGLI", 1600, 1200);
c1->Divide(2,2); //2 righe, 2 colonne
//
TCanvas* c2= new TCanvas("c2", "masse CON TAGLI", 1600, 1200);
c2->Divide(2, 1);


//qui mettiamo le variabili di minimo e massimo dei vari grafici
//
double min_V0=1.107;
double max_V0= 1.124;
//
double min_csi= 1.3;
double max_csi=1.35;
//
double min_omega= 1.6;
double max_omega=1.690;
//
double min_lambda=1.1075;
double max_lambda= 1.124;
//
//costruiamo i vari istogrammi di float 
//
//i seguenti sono per le masse senza tagli
TH1F* hist_V0= new TH1F("hist_V0", "Plot massa V0", 2000, min_V0, max_V0); 
TH1F* hist_csi= new TH1F("hist_csi", "plot massa csi", 1000, min_csi, max_csi); 
TH1F* hist_omega= new TH1F("hist_omega", "plot massa omega", 2000, min_omega, max_omega);
TH1F* hist_V0_lambda= new TH1F("hist_V0_lambda", "plot massa V0 lambda", 1000, min_lambda, max_lambda);
TH1F* hist_V0_alambda= new TH1F("hist_V0_alambda", "plot massa anti lambda", 1000, min_lambda, max_lambda);
//
//i seguenti sono per le masse con tagli su DCA
TH1F* c_hist_V0= new TH1F("c_hist_V0", "Plot massa V0", 1000, min_V0, max_V0); 
TH1F* c_hist_csi= new TH1F("c_hist_csi", "plot massa csi", 1000, min_csi, max_csi); 
TH1F* c_hist_omega= new TH1F("c_hist_omega", "plot massa omega", 1000, 1.65, 1.69);
TH1F* c_hist_V0_lambda= new TH1F("c_hist_V0_lambda", "plot massa V0 lambda", 1000, min_lambda, max_lambda);
TH1F* c_hist_V0_alambda= new TH1F("c_hist_V0_alambda", "plot massa anti lambda", 1000, min_lambda, max_lambda);
//
//questa parte qua serve per non far scomparire tutto 
//
hist_V0->SetDirectory(0);
hist_csi->SetDirectory(0);
hist_omega->SetDirectory(0);
hist_V0_lambda->SetDirectory(0);
hist_V0_alambda->SetDirectory(0);
c_hist_V0->SetDirectory(0);
c_hist_csi->SetDirectory(0);
c_hist_omega->SetDirectory(0);
c_hist_V0_lambda->SetDirectory(0);
c_hist_V0_alambda->SetDirectory(0);
//
//ciclo che riempie le variabili
for (int i=0; i<n; i++){
    tree->GetEntry(i);
  
   //riempiamo gli istogrammi SOLA MASSA SENZA TAGLI
    hist_V0->Fill(mass_V0);
    if(min_csi<= mass_csi && mass_csi<=max_csi) hist_csi->Fill(mass_csi);
     if(min_omega<= mass_omega && mass_omega<= max_omega)   hist_omega->Fill(mass_omega);
    if(min_lambda<= mass_V0_lambda && mass_V0_lambda<=max_lambda)    hist_V0_lambda->Fill(mass_V0_lambda);
    if(min_lambda<= mass_V0_alambda && mass_V0_alambda<= max_lambda)   hist_V0_alambda->Fill(mass_V0_alambda);
    //
    //riempiamo gli istogrammi che CONSIDERANO I TAGLI EFFETTUATI
    if (DCA_casc<=0.1 && DCA_V0<=0.012) {       //0.1, 0.05 non funziona con omega
        c_hist_csi->Fill(mass_csi);
        c_hist_omega->Fill(mass_omega);
        
    }
}
//ora facciamo i fit con le gaussiane
TF1* fit_csi= new TF1("fit_csi", "gaus(0)+ pol3(3)", 1.3, 1.35);
fit_csi->SetParameters(200, 1.322, 0.005, 400);

//
c1->cd(1);
hist_V0->Rebin(7);
hist_V0->Draw();
hist_V0->SetTitle("massa V0");
//
c1->cd(2);
hist_csi->Rebin(7);

hist_csi->Draw();
hist_csi->SetTitle("massa csi");
//
c1->cd(3);
hist_omega->Draw();
hist_omega->SetTitle("massa omega");
//
c1->cd(4);
hist_V0_lambda->Rebin(7);
hist_V0_alambda->Rebin(7);
hist_V0_lambda->Draw();
hist_V0_alambda->Draw("SAME");
hist_V0_lambda->SetTitle("massa lambda");
hist_V0_alambda->SetLineColor(kGreen);


c2->cd(1);
c_hist_csi->Rebin(10);
c_hist_csi->Fit("fit_csi", "R");
cout<<"il p value del fit massa csi è "<<fit_csi->GetProb()<<endl;
c_hist_csi->SetTitle("massa csi");
c_hist_csi->Draw();

c2->cd(2);
c_hist_omega->Rebin(30);
c_hist_omega->SetTitle("massa omega");
c_hist_omega->Draw();








analisi->Close();











    
}