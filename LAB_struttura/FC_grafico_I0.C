#include<iostream>
#include<vector>
#include<cmath>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TGaxis.h"
#include "TPad.h"

using namespace std;


void FC_graph_I0(){
    vector<double> lambda={
        437.3694,
        447.737,
        458.0709,
        468.371,
        478.637,
        488.8688,
        499.0663,
        509.2294,
        519.3577,
        529.4513,
        539.5099,
        549.5334,
        559.5216,
        569.4743,
        579.3915,
        589.2729,
        599.1183,
        608.9277,
        618.7009,
        628.4376,
        630.3806,
        632.3221,
        634.2621,
        636.2007,
        638.1378,
        640.0734,
        642.0076,
        643.9403,
        645.8715,
        647.8013,
        649.7295,
        651.6563,
        653.5817,
        655.5055,
        657.4279,
        659.3487,
        661.2681,
        663.1861,
        667.0174,
        671.7983,
        676.5698,
        681.332,
        686.0848,
        695.5623,
        705.0022,
        714.4042,
        723.7682,
        733.0941,
    };
    vector<double> err_lambda={9.4262,
        9.0141,
        8.6103,
        8.2154,
        7.8302,
        7.4557,
        7.093,
        6.7435,
        6.4088,
        6.0909,
        5.7919,
        5.5143,
        5.261,
        5.035,
        4.8395,
        4.6777,
        4.5524,
        4.4659,
        4.4197,
        4.4144,
        4.4182,
        4.4236,
        4.4306,
        4.4391,
        4.4492,
        4.4608,
        4.474,
        4.4886,
        4.5048,
        4.5223,
        4.5413,
        4.5617,
        4.5835,
        4.6067,
        4.6311,
        4.6569,
        4.6839,
        4.7122,
        4.7723,
        4.8539,
        4.9423,
        5.0369,
        5.1373,
        5.3537,
        5.5884,
        5.8383,
        6.1008,
        6.3736,
    };
    vector<double> tensione={50.4,	
        53.93,	
        54.39,	
        55.8,	
        58.88,	
        64.62,	
        68.56,	
        73.36,	
        77.55,	
        80.16,	
        81.86,	
        84.45,	
        86,
        87.41,	
        89.68,	
        92.97,	
        94.62,	
        96.66,	
        98.1,	
        98.67,	
        98.64,	
        98.86,	
        98.85,	
        98.9,	
        99.19,	
        99.1,	
        99.3,	
        99.23,	
        99.04,	
        99.37,	
        98.76,	
        98.92,	
        98.95,	
        98.7,	
        98.82,	
        98.3,	
        98.14,	
        98.07,	
        97.3,	
        96.55,	
        95.63,	
        94.21,	
        92.12,	
        85.21,	
        76.42,	
        68.69,	
        57.18,	
        48.32,	
    };
    vector<double> err_tensione={2,
        2,
        2,
        2,
        2,
        2,
        2,
        2,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
        4,
    };
    int len= lambda.size();

    TCanvas* c1= new TCanvas("c1", "tensione", 800, 600);

    TGraphErrors* gr1= new TGraphErrors(len, lambda.data(), tensione.data(), err_lambda.data(), err_tensione.data());
    
    gr1->SetLineColor(860+5);
    TPad* p1= new TPad("p1", "", 0, 0, 1,1);
    TPad* p2= new TPad("p1", "", 0, 0, 1,1);
    p2->SetFillStyle(4000); //è trasparente

    p1->Draw();
    p1->cd();
    gr1->SetTitle("Tensione e lambda senza vetrino");
    gr1->GetYaxis()->SetTitle("Tensione");
    gr1->GetYaxis()->SetAxisColor(kBlack);
    gr1->GetYaxis()->SetLabelColor(kBlack);
    gr1->GetYaxis()->SetTitleColor(kBlack);

   
    gr1->GetXaxis()->SetTitle("#lambda (nm)");

    gr1->Draw("ALP");
    gPad->Update();
    gPad->SetGrid();
   
    c1->Print("grafico_lambda-tensione_no_vetrino.png", "png");


}