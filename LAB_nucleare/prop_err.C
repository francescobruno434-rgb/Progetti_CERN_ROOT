#include<iostream>
#include "TF1.h"
#include<cmath>

using namespace std;

double EfficiencyFalling(double *x, double *par) {
  return par[0]/(1+exp((x[0] - par[1])/par[2]))+par[3];
}


double EfficiencyRising(double *x, double *par) {
  return par[0]/(1+exp((par[1] - x[0])/par[2]))+par[3];
}


double err(double dery, double erry, double dera, double erra, double derb, double errb, double derc, double errc, double derd, double errd){
    double var= pow(dery, 2)* pow(erry, 2)+ pow(dera, 2)* pow(erra, 2)+ pow(derb, 2)* pow(errb, 2)+ pow(derc, 2)* pow(errc, 2)+ pow(derd, 2)* pow(errd, 2);
    double error= pow(var, 0.5);
    return error;
}




void prop_err(){
//questa è la formula generale; non ci serve a niente, ma solo come reminder; la x è in realtà la y
TF1* x_rising= new TF1("x_rising", "[1]-[2]*log([0]/(x-[3])-1)", -40, 0); 

//ora, la stessa cosa, ma per calcolare la derivata rispetto a y
//questi i parametri a cui inizializzeremo a, b, c, d
double par_in_x[]={13.4, -30.9, 1.1, 0.004};
double der_y=x_rising->Derivative(6.75, par_in_x);
cout<<"La derivata della x rispetto alla y vale " << der_y <<endl;

//ora, stessa cosa di prima ma rispetto al parametro [0], e via così
TF1* x_ris_a= new TF1("x_ris_a", "[1]-[2]*log(x/([0]-[3])-1)", -40, 0); 
double par_in_a[]={6.75, -30.9, 1.1, 0.004};
double der_a=x_ris_a->Derivative(13.4, par_in_a);
cout<<"La derivata della x rispetto alla a vale " << der_a <<endl;

//DERIVATA RISPETTO A B
TF1* x_ris_b= new TF1("x_ris_b", "x-[2]*log([1]/([0]-[3])-1)", -40, 0); 
double par_in_b[]={6.75, 13.4, 1.1, 0.004};
double der_b=x_ris_b->Derivative(-30.9, par_in_b);
cout<<"La derivata della x rispetto alla b vale " << der_b <<endl;

//derivata rispetto a C
TF1* x_ris_c= new TF1("x_ris_c", "[2]-x*log([1]/([0]-[3])-1) ", -40, 0); 
double par_in_c[]={6.75, 13.4, -30.9, 0.004};
double der_c=x_ris_c->Derivative(1.1, par_in_c);
cout<<"La derivata della x rispetto alla c vale " << der_c <<endl;

//derivata rispetto alla d
TF1* x_ris_d= new TF1("x_ris_d", "[2]-[3]*log([1]/([0]-x)-1)", -40, 0); 
double par_in_d[]={6.75, 13.4, -30.9, 1.1 };
double der_d=x_ris_d->Derivative(0.004, par_in_d);
cout<<"La derivata della x rispetto alla d vale " << der_d<<endl;


//RISULTATO FINALE
double errore= err(der_y, 0.05, der_a, 0.1, der_b, 0.2, der_c, 0.1, der_d, 0.005);
double param[]={13.4, -30.9, 1.1, 0.004};
double x[]={6.75};
double valore= x_rising->EvalPar(x, param);

cout<<"la funzione vale "<<valore<<endl;
cout<<"L'errore dunque vale:  "<<errore<<endl;











}