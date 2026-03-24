#include<iostream>
#include<cmath>
#include<vector>
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
using namespace std;






void  TESIt_plot_1(){
//cominciamo cercando il barione xi, che ha una massa energetica di circa 1.3 GeV
//leggo il file dove ci sono i TTree
TFile* analisi= TFile("AnalysisResults_280234.root", "READ");
//
if(analisi->IsOpen()){
    cout<<"file aperto correttamente"<<endl;
}
//leggo il TTree
TTree* tree= (TTree*)analisi->Get("fTreeCascade");
//
cout<<"Gli ingressi di tree sono"<<tree->GetEntries()<<endl;
double massa=0; //creo la variabile massa in cui metterò i dati del tree
//
//Collego il Branch di mio interesse a questa variabile
tree->SetBranchAddress("fTreeCascVarV0Mass", &massa);
//
//bisogna capire quante Entries (righe) ci sono; 
int n= tree->GetEntries();
//
//a questo punto, creiamo il nostro istogramma e il canvas
TCanvas* c1= new TCanvas("c1", "massa csi ", 800, 600);
//
TH1D* hist= new TH1D(); //non voglio ancora specificare il numero di bin; ci penso dopo
//
int num_dati=0; //numero di dati nel mio istogramma
//ora ciclo
for (int i=0; i<n; i++){
    tree->GetEntry(i);
    if (massa>1.114 & massa<1.118){
        hist->Fill(massa);
        num_dati++;
    }
}
//il numero dei bin potrebbe essere la radice dei dati?
double n_bins= pow(num_dati, 0.5);
int n_def= (int) n_bins;
//
hist->SetBins(n_def, 1.114, 1.118);
//
hist->Draw();

analisi->Close();











    
}