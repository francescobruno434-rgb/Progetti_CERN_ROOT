#include<iostream>
#include<cmath>


using namespace std;



void prova(){

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
    tree->SetBranchAddress("fTreeCascVarMassAsXi", &mass_csi);
    tree->SetBranchAddress("fTreeCascVarCharge", &charge);  
    float DCACascDaughters=0;
    tree->SetBranchAddress("fTreeCascVarDCACascDaughters", &DCACascDaughters);
    float DCABachToPrimVtx=0;
    tree->SetBranchAddress("fTreeCascVarDCABachToPrimVtx", &DCABachToPrimVtx);
    float DCAV0Daughters=0;
    tree->SetBranchAddress("fTreeCascVarDCAV0Daughters", &DCAV0Daughters );
    float DCAV0ToPrimVtx=0;
    tree->SetBranchAddress("fTreeCascVarDCAV0ToPrimVtx", &DCAV0ToPrimVtx);
    float DCAPosToPrimVtx=0;
    tree->SetBranchAddress("fTreeCascVarDCAPosToPrimVtx", &DCAPosToPrimVtx);
    float DCANegToPrimVtx=0;
    tree->SetBranchAddress("fTreeCascVarDCANegToPrimVtx", &DCANegToPrimVtx);
    float CascCosToPointingAngle=0;
    tree->SetBranchAddress("fTreeCascVarCascCosPointingAngle", &CascCosToPointingAngle);
    float CascDCAtoPVxy=0;
    tree->SetBranchAddress("fTreeCascVarCascDCAtoPVxy", &CascDCAtoPVxy);
    float CascRadius=0;
    tree->SetBranchAddress("fTreeCascVarCascRadius", &CascRadius);
    float V0CosPointingAngle=0;
    tree->SetBranchAddress("fTreeCascVarV0CosPointingAngle", &V0CosPointingAngle);
    float V0Radius=0;
    tree->SetBranchAddress("fTreeCascVarV0Radius", &V0Radius);




    int len_tot= tree->GetEntries();
    
    cout<<"lunghezza totale "<< len_tot <<endl;
    int num_part_DCACascDaughter=0;
     int num_part_DCABachToPrimVtx=0;
    int num_part_DCAV0Daughters=0;
    int num_part_DCAV0ToPrimVtx=0;
    int num_part_DCAPosToPrimVtx=0;
    int num_part_DCANegToPrimVtx=0;
    int num_part_CascCosToPointingAngle=0;
    int num_part_CascDCAtoPVxy=0;
    int num_part_CascRadius=0;
    int num_part_V0CosPointingAngle=0;
    int num_part_V0Radius=0;





    for(int i=0; i<len_tot; i++){
        tree->GetEntry(i);
        if(DCACascDaughters<0.1){
            num_part_DCACascDaughter++;
        }
        if(DCABachToPrimVtx>0.1){
            num_part_DCABachToPrimVtx++;
        }
        if(DCAV0Daughters<0.2){
            num_part_DCAV0Daughters++;
        }
        if(DCAV0ToPrimVtx<1){
            num_part_DCAV0ToPrimVtx++;
        }
        if(DCAPosToPrimVtx<1){
            num_part_DCAPosToPrimVtx++;
        }
        if(DCANegToPrimVtx<1){
            num_part_DCANegToPrimVtx++;
        }
        if(CascCosToPointingAngle>=0.97){
            num_part_CascCosToPointingAngle++;
        }
        if(CascDCAtoPVxy<0.2){
            num_part_CascDCAtoPVxy++;
        }
        if(CascRadius<10){
            num_part_CascRadius++;
        }
        if(V0CosPointingAngle>0.99){
            num_part_V0CosPointingAngle++;
        }
        if(V0Radius<20){
            num_part_V0Radius++;
        }






    }

    cout<<"DCACascDaughters <0.1 "<<num_part_DCACascDaughter<<endl;
    cout<<"DCABachToPrimVtx >0.1 "<< num_part_DCABachToPrimVtx<<endl;
    cout<<"DCAVoDaughters <0.1 "<< num_part_DCAV0Daughters<<endl;
    cout<<"V0ToPrimVtx <1 "<< num_part_DCAV0ToPrimVtx<<endl;
    cout<<"DCAPosToPrimVtx <1 "<< num_part_DCAPosToPrimVtx<<endl;
    cout<<"DCANegToPrimVtx <1 "<<num_part_DCANegToPrimVtx<<endl;
    cout<<"CascCOsPointingAngle >0.999 "<< num_part_CascCosToPointingAngle<<endl;
    cout<<"CascDCATOPvtx <0.2 "<<num_part_CascDCAtoPVxy<<endl;
    cout<<"CascRadius <10 "<<num_part_CascRadius<<endl;
    cout<<"V0CosPointingAngle >0.999 "<< num_part_V0CosPointingAngle<<endl;
    cout<<"V0radius <20 "<< num_part_V0Radius<<endl;



    

    }














