#include<iostream>
#include<cmath>
#include<vector>
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"
using namespace std;

/*l'obiettivo di questo file è fare tagli sui seguenti valori:
DCAV0toPrimaryVertex
DCAPosToPv
DCANegToPv
V0radius
V0cosPa (il più importante)
DCABAchToPv
CascadecosPA (altro importante)
CascDCAToPV
cascDcaToPVxy
CascRadius
V0cosPA
*/

void TESIt_tagli_2(){
    //
    //
    TFile* analisi= new TFile("AnalysisResults_280234.root", "READ");
    //
    TTree* tree= (TTree*) analisi->Get("PWGLF_StrVsMult/fTreeCascade");
    //
    TCanvas* c1= new TCanvas("c1", "MASSA senza tagli", 1000, 800);
    //
    c1->Divide(1, 2);
    //di seguito i nomi delle variabili a cui saranno associati gli address dei TTree
    float mass_csi=0;
    int charge=0;
    //
    //creiamo gli istogrammi con dentro solo le masse delle csi e delle anti-csi (antiparticelle di carica positiva)
    TH1F* hmass_csi= new TH1F("mass_csi", "massa delle particelle \Csi^-", 200, 1.3, 1.35);
    TH1F* hmass_anti_csi= new TH1F("mass_anti_csi", "massa delle anti particelle \Csi^+", 200, 1.3, 1.35);
    //
    //
    tree->SetBranchAddress("fTreeCascVarMassAsXi", &mass_csi);
    tree->SetBranchAddress("fTreeCascVarCharge", &charge);
    //
    //numero di entries
    int len= tree->GetEntries();
    //
    //
    for(int i=0; i<len; i++){
        tree->GetEntry(i);
        if(charge<=0){
            hmass_csi->Fill(mass_csi);
        }
        if(charge>0){
            hmass_anti_csi->Fill(mass_csi);
        }

    }
    //funzioni di fit massa csi
    TF1* fit_massa_csi= new TF1("fit_massa_csi", "gaus(0)+ pol3(3)", 1.3, 1.35);
    fit_massa_csi->SetParameters(350, 1.32171, 0.003, 20750, -2671, -2280, -3400);
    /*fit_massa_csi->SetParLimits(0, 300, 350);
    fit_massa_csi->SetParLimits(1, 1.321, 1.32171);
    fit_massa_csi->SetParLimits(2, 0.003, 0.004);
    fit_massa_csi->SetParLimits(3, 17290, 17300);
    fit_massa_csi->SetParLimits(4, -2670, -2671);
    fit_massa_csi->SetParLimits(5, -2240, -2241);
    fit_massa_csi->SetParLimits(6, -2020, -2021);*/

   
    //
    //funzioni di fit anti csi
    TF1* fit_massa_anti_csi= new TF1("fit_massa_anti_csi", "gaus(0)+ pol3(3)", 1.315, 1.33);
    fit_massa_anti_csi->SetParameters(600, 1.321, 0.05, 4800);
    //
    //disegniamo gli istogrammu
    c1->cd(1);
    hmass_csi->Fit("fit_massa_csi", "R");
    hmass_csi->Draw();
    hmass_csi->SetTitle("massa della csi");
     cout<<"il p-value è: "<<fit_massa_csi->GetProb()<<endl;

    c1->cd(2);
    hmass_anti_csi->Fit("fit_massa_anti_csi", "R");
    hmass_anti_csi->Draw();
    hmass_anti_csi->SetTitle("massa anti csi");
     cout<<"il p-value è: "<<fit_massa_anti_csi->GetProb()<<endl;
    










}