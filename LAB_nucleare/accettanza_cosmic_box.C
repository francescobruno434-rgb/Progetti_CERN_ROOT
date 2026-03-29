#include<iostream>
#include<vector>
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"

usig namespace std;

void accettanza_cosmic_box(){
    //
    vector<double> distanze={};
    vector<double> err_distanze={};
    //
    vecrtor<double> conteggi_doppi={};
    vector<double> err_conteggi_doppi={};
    //
    //
    //
    vector<double> tempo_daq={};
    vector<double> err_tempo_daq={};
    //
    vector<double> rate={};
    vector<double> err_rate={};

    //
    //cerchiamo il numero di elementi di questi vettori
    int len= distanze.size();
    //
    //errori sulle distanze (0.2)
    for(int i=0; i<len; i++){
        err_distanze.push_back(0.2);
    }
    //
    //errrori sul tempo
    double 
    
























}