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
//
cout<<"Gli ingressi di tree sono "<<tree->GetEntries()<<endl;
float massa=0; //creo la variabile massa in cui metterò i dati del tree
//
//Collego il Branch di mio interesse a questa variabile
tree->SetBranchAddress("fTreeCascVarV0Mass", &massa);
//
//bisogna capire quante Entries (righe) ci sono; 
int n= tree->GetEntries();
//

//
TH1F* hist= new TH1F("hist", "Plot massa", 10, 1.107, 1.124); //non voglio ancora specificare il numero di bin; ci penso dopo
//
int num_dati=0; //numero di dati nel mio istogramma
//ora ciclo

float massa_min=pow(10, 15);
float massa_max=0;
for (int i=0; i<n; i++){
    tree->GetEntry(i);
    if (massa<massa_min ){
        massa_min=massa;
    }
    else if(massa> massa_max){
        massa_max= massa;
    }
   
    hist->Fill(massa);
    num_dati++;

   /* if (massa>1.114 && massa<1.118){
        hist->Fill(massa);
        num_dati++;
    }*/
}
//il numero dei bin potrebbe essere la radice dei dati?
/*double n_bins= pow(num_dati, 0.5);
int n_def= (int) n_bins;*/
//
//hist->SetBins(n_def, 1.114, 1.118);
//
//a questo punto, creiamo il nostro istogramma e il canvas
TCanvas* c1= new TCanvas("c1", "massa csi ", 800, 600);
cout<<"la massa massima è "<<massa_max<<endl;
cout<<"la massa minima è "<<massa_min<<endl;
hist->Draw("");

analisi->Close();











    
}