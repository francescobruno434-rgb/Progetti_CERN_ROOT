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


TH1F* hanti_DCACascDaughters= new TH1F("hanti_DCACascDaughters",200, 0, 0.51);
TH1F* hanti_DCACascDaughters_fondo= new TH1F("hanti_DCACascDaughters_fondo", 200, 0, 0.51);
TH1F* hanti_DCACascDaughters_segnale= new TH1F("hanti_DCACascDaughters_segnale", 200, 0, 0.51);
hanti_DCACascDaughters->SetLineColor(6);  // fucsia l'originale
hanti_DCACascDaughters_fondo->SetLineColor(2); //rosso il fondo
hanti_DCACascDaughters_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCABachToPrimVtx= new TH1F("hanti_DCABachToPrimVtx",200, 0, 30);
TH1F* hanti_DCABachToPrimVtx_fondo= new TH1F("hanti_DCABachToPrimVtx_fondo", 200, 0, 30);
TH1F* hanti_DCABachToPrimVtx_segnale= new TH1F("hanti_DCABachToPrimVtx_segnale", 200, 0, 30);
hanti_DCABachToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCABachToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCABachToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCAV0Daughters= new TH1F("hanti_DCAV0Daughters",200, 0, 1.05);
TH1F* hanti_DCAV0Daughters_fondo= new TH1F("hanti_DCAV0Daughters_fondo", 200, 0, 1.05);
TH1F* hanti_DCAV0Daughters_segnale= new TH1F("hanti_DCAV0Daughters_segnale", 200, 0, 1.05);
hanti_DCAV0Daughters->SetLineColor(6);  // fucsia l'originale
hanti_DCAV0Daughters_fondo->SetLineColor(2); //rosso il fondo
hanti_DCAV0Daughters_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCAV0ToPrimVtx= new TH1F("hanti_DCAV0ToPrimVtx",200, 0, 25);
TH1F* hanti_DCAV0ToPrimVtx_fondo= new TH1F("hanti_DCAV0ToPrimVtx_fondo", 200, 0, 25);
TH1F* hanti_DCAV0ToPrimVtx_segnale= new TH1F("hanti_DCAV0ToPrimVtx_segnale", 200, 0, 25);
hanti_DCAV0ToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCAV0ToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCAV0ToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCAPosToPrimVtx= new TH1F("hanti_DCAPosToPrimVtx",200, 0, 38);
TH1F* hanti_DCAPosToPrimVtx_fondo= new TH1F("hanti_DCAPosToPrimVtx_fondo", 200, 0, 38);
TH1F* hanti_DCAPosToPrimVtx_segnale= new TH1F("hanti_DCAPosToPrimVtx_segnale", 200, 0, 38);
hanti_DCAPosToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCAPosToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCAPosToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_DCANegToPrimVtx= new TH1F("hanti_DCANegToPrimVtx",200, 0, 38);
TH1F* hanti_DCANegToPrimVtx_fondo= new TH1F("hanti_DCANegToPrimVtx_fondo", 200, 0, 38);
TH1F* hanti_DCANegToPrimVtx_segnale= new TH1F("hanti_DCANegToPrimVtx_segnale", 200, 0, 38);
hanti_DCANegToPrimVtx->SetLineColor(6);  // fucsia l'originale
hanti_DCANegToPrimVtx_fondo->SetLineColor(2); //rosso il fondo
hanti_DCANegToPrimVtx_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_CascCosToPointingAngle= new TH1F("hanti_CascCosToPointingAngle",200, 0.948, 1.002);
TH1F* hanti_CascCosToPointingAngle_fondo= new TH1F("hanti_CascCosToPointingAngle_fondo", 200, 0.948, 1.002);
TH1F* hanti_CascCosToPointingAngle_segnale= new TH1F("hanti_CascCosToPointingAngle_segnale", 200, 0.948, 1.002);
hanti_CascCosToPointingAngle->SetLineColor(6);  // fucsia l'originale
hanti_CascCosToPointingAngle_fondo->SetLineColor(2); //rosso il fondo
hanti_CascCosToPointingAngle_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_CascDCAtoPVxy= new TH1F("hanti_CascDCAtoPVxy",200, 0, 11);
TH1F* hanti_CascDCAtoPVxy_fondo= new TH1F("hanti_CascDCAtoPVxy_fondo", 200, 0, 11);
TH1F* hanti_CascDCAtoPVxy_segnale= new TH1F("hanti_CascDCAtoPVxy_segnale", 200, 0, 11);
hanti_CascDCAtoPVxy->SetLineColor(6);  // fucsia l'originale
hanti_CascDCAtoPVxy_fondo->SetLineColor(2); //rosso il fondo
hanti_CascDCAtoPVxy_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_CascRadius= new TH1F("hanti_CascRadius",200, 0, 95);
TH1F* hanti_CascRadius_fondo= new TH1F("hanti_CascRadius_fondo", 200, 0, 95);
TH1F* hanti_CascRadius_segnale= new TH1F("hanti_CascRadius_segnale", 200, 0, 95);
hanti_CascRadius->SetLineColor(6);  // fucsia l'originale
hanti_CascRadius_fondo->SetLineColor(2); //rosso il fondo
hanti_CascRadius_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_V0CosPointingAngle= new TH1F("hanti_V0CosPointingAngle",200, 0.979, 1.001);
TH1F* hanti_V0CosPointingAngle= new TH1F("hanti_V0CosPointingAngle_fondo", 200, 0.979, 0.001);
TH1F* hanti_V0CosPointingAngle= new TH1F("hanti_V0CosPointingAngle_segnale", 200, 0, 0.6);
hanti_V0CosPointingAngle->SetLineColor(6);  // fucsia l'originale
hanti_V0CosPointingAngle_fondo->SetLineColor(2); //rosso il fondo
hanti_V0CosPointingAngle_segnale->SetLineColor(3); //verde segnale
//
TH1F* hanti_V0Radius= new TH1F("hanti_V0Radius",200, 0, 200);
TH1F* hanti_V0Radius= new TH1F("hanti_V0Radius_fondo", 200, 0, 200);
TH1F* hanti_V0Radius= new TH1F("hanti_V0Radius_segnale", 200, 0, 200);
hanti_V0Radius->SetLineColor(6);  // fucsia l'originale
hanti_V0Radius_fondo->SetLineColor(2); //rosso il fondo
hanti_V0Radius_segnale->SetLineColor(3); //verde segnale
//
