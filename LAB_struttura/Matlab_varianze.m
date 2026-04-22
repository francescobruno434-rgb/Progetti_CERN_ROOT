% l'obiettivo è calcolare le covarianze con valori di ua variabili; per
% questo definiamo fin da subito una funzione
syms a b c d e f e f chn ua l


%covMatrix = zeros(7); % Initialize a 7x7 covariance matrix
%covMatrix(1,1) = 1; % Set the variance for the first parameter
%covMatrix(2,2) = 1; % Set the variance for the second parameter
% Continue initializing the covariance matrix as needed

covMatrix= [
    0.1846,  -0.001697 ,  1.471e-06 , -3.188e-10, 0, 0,0;
    -0.001697, 1.599e-05,  -1.399e-08,  3.047e-12, 0, 0,0;
     1.471e-06,  -1.399e-08,  1.294e-11 ,  -2.936e-15, 0, 0, 0;
      -3.188e-10 ,  3.047e-12,  -2.936e-15,  6.864e-19, 0, 0, 0;
      0, 0, 0, 0,  160.6 , -0.106, 0;
      0, 0, 0, 0,  -0.106 ,  7.92e-05, 0;
      0, 0, 0, 0, 0, 0, 1
      ];

% ricordo chn= ((ua-e)/f)

l= a+ b* ((ua-e)/f)+ c* ((ua-e)/f)^2+ d* ((ua-e)/f)^3;
gradient= jacobian(l, [a, b, c, d, e, f, ua]); 

%qui ci sono i parametri dello spettrometro (f sta per fit)
af= 339.509 ;
bf=  0.219315;
cf= -6.74829e-06;
df=  -2.28895e-10;
%di seguito invece definiamo i parametri del fit lineare del monocromatore
ef=   407.134;
ff= 0.205179 ;
% qui di seguito, definiamo la matrice delle covarianze, che non sarà 6x6,
% ma 7x7, perchè va considerato l'errore sulle ua (varianza pari a 1)
uaf= 500;

%ora, valori numerici
gradiente_num= double(subs(gradient, [a, b, c, d, e, f, ua], [af, bf, cf, df, ef, ff, uaf]));
l_num= double(subs(l,  [a, b, c, d, e, f, ua], [af, bf, cf, df, ef, ff, uaf] ));
% Calculate the variance of the linear fit using the covariance matrix
varFit = gradiente_num * covMatrix * gradiente_num';
sigma_fit= sqrt(varFit);
% Display the results
fprintf('Calculated sigma_fit: %.4f\n', sigma_fit);
fprintf('Linear fit value (l_num): %.4f\n', l_num);


%parte nuova: 
J_funz= matlabFunction(gradient, 'Vars', [a, b, c, d, e, f, ua]);
l_funz=matlabFunction(l, 'Vars',  [a, b, c, d, e, f, ua] );

ua_punti=[500,	510,	520,	530,	540,	550,	560,	570,	580,	590,	600,	610,	620,	630,	640,	650,	660,	670,	680,	682,	684,	686,	688,	690,	692,	694,	696,	698,	700,	702,	704,	706,	708,	710,	712,	714,	716,	718,	720,	722,	724,	726,	730,	735,	740,	745,	750,	760,	770,	780,	790,	800];

errori= zeros(1, 52);
valori_l= zeros(1, 52);

for i = 1:length(ua_punti)
    gradiente = J_funz(af, bf, cf, df, ef, ff, ua_punti(i));
    varianza= gradiente* covMatrix* gradiente'; 
    l_nuova= l_funz(af, bf, cf, df, ef, ff, ua_punti(i));
    errori(i) = sqrt(varianza);
    valori_l(i)= l_nuova;
end

T= table(ua_punti', valori_l', errori', 'VariableNames', {'Unità arbitrarie', 'valori l', 'errori l'});
disp(T);
    