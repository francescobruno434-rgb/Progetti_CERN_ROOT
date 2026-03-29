#include<iostream>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include <cmath>
#include <vector>


using namespace std;




//definizione di funzioni che saranno utili
double err_rel_divisione(double err_num, double err_den){
    double err_quad= pow(err_num, 2)+ pow(err_den, 2);
    double err_rel= pow(err_quad, 0.5);
    return err_rel;
}








void LAB_nucl_coeff_att(){


    //++++++++++++++++++++++++++++++++++++++++++++++SCRIVERE NEI SEGUENTI VETTORI!!
    //vettore delle coincidenze
    vector<double> rate= {0.4543532809, //NB: questa è quella sul tetto
        0.31796963294187,
        0.267486303987769,
        0.212285350583223,
       
        0.217774547376768,
        
         };
    //vettore errore sul rate
    vector<double> err_rate={0.02870389453,
        0.0210217226114178,
        0.0220484048715267,
        0.0183298550087976,
       
        0.0186546323932292,
        
    };
    //vettore profondità CALCOLATA DALL'ALTO! il tetto è 0 per intendersi; la misura è in m (contano solo le solette)
    vector<double> profondità={0,
        1.39,
        2.32,


        3.02,
        3.7,
           };
    //
    vector<double> err_profondità={0,
        0.014142135623731,
        0.02,


        0.0244948974278318,
        0.0282842712474619,
        };
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++NON SCRIVERE PIU'!

    vector<double> conteggi={301,
        303,
        200,
        200,
        201,};
    vector<double> err_conteggi={17,
        17,
        14,
        14,
        
        14,};
    vector<double> tempo_daq={619,
        866,
        668,
        819,
        805,};
    vector<double> err_tempo_daq={1, 1, 1, 1, 1};

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TCanvas *c1= new TCanvas("c1", "Misura coeff attenuazione", 800, 600);
    //
    TGraphErrors* gr1= new TGraphErrors(rate.size(), profondità.data(), rate.data(), err_profondità.data(), err_rate.data() );
    //
    gr1->GetYaxis()->SetRangeUser(0, 0.6);
    gr1->GetXaxis()->SetRangeUser(-2, 4);
    gr1->GetXaxis()->SetTitle("x (m)");
    gr1->GetYaxis()->SetTitle("Rate (Hz)");
    gr1->SetTitle("Attenuazione del rate vs spessore attraversato");
   
   
    //
    //funzione di fit
    TF1* fit= new TF1("fit", "[0]*exp(-[1]*x)");
    fit->SetParameters(0.45, 0.22);
    //fit->SetParLimits(1, 0.14, 0.19);
    gr1->Fit("fit");
    cout<<"Il p-value è "<<endl;
   cout<< fit->GetProb()<<endl;
     gr1->Draw("AP.");
     //c1->Print("coeff_attenuazione.png", "png");

        int len= 5;
        for (int i=0; i<len; i++){
            //profondità conteggi tempo daq, rate
            cout<<"$ ( "<< profondità[i]<< " \\pm "<<err_profondità[i]<< " )  $ & $ ( "<<conteggi[i]<< " \\pm "<<err_conteggi[i]<< " )  $ & $ ( "<< tempo_daq[i]<< " \\pm " << err_tempo_daq[i]<< " )  $ & $ ( "<< rate[i]<< " \\pm " <<err_rate[i]<<  ") $ \\\\ \\hline" <<endl;
        }






























}



