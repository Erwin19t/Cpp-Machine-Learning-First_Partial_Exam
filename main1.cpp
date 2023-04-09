/*
Programa de Regresion Lineal

Compilacion: g++ main1.cpp -o Ejecutable -std=c++11 -lm
Ejecucion: ./Ejecutable
*/

#include <iostream>
#include <unistd.h>
#include <math.h>
#define Alpha 0.00000005

using namespace std;

double Initial_Theta(int);
double Evaluate(double, double, double, double);
double MSE(double, double);
double Grad_MSE(double, double, double, int);
double Relative_Error(double, double, double, double, double, double);

int main(){
    //Vector de Edades
    double X[6] = {17.5, 22, 29.5, 44.5, 64.5, 80};
    //Vector de muertes
    double Y[6] = {38, 36 , 24, 20, 18, 28};
    double Y_g[6] = {0};
    double Theta_ant[3];            
    double Theta_act[3];
    double mse   = 0;
    double GMSE[3] = {0};
    double Error = 100;
    double Evaluation = 0;
    int i, j;
    int Counter = 0;
 
    //Descomentar esta seccion para probar con valores iniciales aleatorios
    /*
    Theta_ant[0] = Initial_Theta(1);
    sleep(1);
    Theta_ant[1] = Initial_Theta(2);
    sleep(1);
    Theta_ant[2] = Initial_Theta(3);
    */
    Theta_ant[0] = 7;
    Theta_ant[1] = 1;
    Theta_ant[2] = 6;

    Theta_act[0] = Theta_ant[0];
    Theta_act[1] = Theta_ant[1];
    Theta_act[2] = Theta_ant[2];


    //cout<<"Pesos deseados = [5 ; 1]"<<endl;
    cout<<"Pesos iniciales= ["<<Theta_act[0]<<" ; "<<Theta_act[1]<<" ; "<<Theta_act[2]<<"]"<<endl<<endl;

    //while(Counter <= 500){
    while(Error >= (1*pow(10,-6))){
        //Se evalua la funcion y se calcula el MSE
        for(i = 0; i < 5; i++){
            Y_g[i] = Evaluate(Theta_act[0], Theta_act[1], Theta_act[2], X[i]);
            mse = MSE(Y_g[i], Y[i]) + mse;
        }
        mse = mse/5;

        //Se calcula el Gradiente
        for(j = 0; j < 3; j++){
            for(i = 0; i < 5; i++){
                GMSE[j] = Grad_MSE(Y_g[i], Y[i], X[i], j) + GMSE[j];
            }
            GMSE[j] = GMSE[j]*2/5;
        }

        //Paso 5: Se calcula el nuevo vector Theta
        Theta_act[0] = Theta_ant[0] - Alpha*GMSE[0];
        Theta_act[1] = Theta_ant[1] - Alpha*GMSE[1];
        Theta_act[2] = Theta_ant[2] - Alpha*GMSE[2];

        //Se calcula el Error
        Error = Relative_Error(Theta_act[0], Theta_act[1], Theta_act[2], Theta_ant[0], Theta_ant[1], Theta_ant[2]);

        if(Counter%2 == 0){
            //Chingo de Impresiones
            cout<<"Iteracion "<<Counter<<endl;
            cout<<"Error Medio Cuadratico = "<<mse<<endl;
            cout<<"Gradiente del MSE  = ["<<GMSE[0]<<" ; "<<GMSE[1]<<" ; "<<GMSE[2]<<"]"<<endl;
            cout<<"Nuevo vector Theta = ["<<Theta_act[0]<<" ; "<<Theta_act[1]<<" ; "<<Theta_act[2]<<"]"<<endl;
            cout<<"Error = "<<Error<<endl<<endl;
        }

        //Actualizamos el vector theta anterior,
        //aumentamos contador de iteraciones
        //y reseteamos algunas variables
        Theta_ant[0] = Theta_act[0];
        Theta_ant[1] = Theta_act[1];
        Theta_ant[2] = Theta_act[2];
        mse = 0;
        GMSE[0] = 0;
        GMSE[1] = 0;
        GMSE[2] = 0;  
        Counter++;
    }
    cout<<"El alpha utilizado fue:"<<Alpha<<endl;
    cout<<"Theta0 final: "<<Theta_act[0]<<endl;
    cout<<"Theta1 final: "<<Theta_act[1]<<endl;
    cout<<"Theta2 final: "<<Theta_act[2]<<endl;
    Evaluation = Evaluate(Theta_act[0], Theta_act[1], Theta_act[2], 40);
    cout<<"La cantidad de muertes para la edad de 40 es:"<<Evaluation<<endl;;
    Evaluation = Evaluate(Theta_act[0], Theta_act[1], Theta_act[2], 60);
    cout<<"La cantidad de muertes para la edad de 60 es:"<<Evaluation<<endl;;
    return 0;
}

//Paso 1: Inicializar los pesos aleatoriamente
double Initial_Theta(int id){
    double Theta;
    srand(id + (int)time(NULL));
    Theta = 0.1 + ((rand()%(10000))/1000.00f);
    return Theta;
}

//Paso 2: Evaluacioes
double Evaluate(double theta_0, double theta_1, double theta_2, double x){
    return theta_0 + theta_1*(x) + theta_2*(x*x);
}

//Paso 3: Calculo de Error Medio Cuadratico
double MSE(double y_g, double y){
    return pow((y_g - y),2);
}

//Paso 4: Calculo del Gradiente del MSE
double Grad_MSE(double y_g, double y, double x, int exp){
    return (y_g - y)*pow(x,exp);
}

//Paso 6: Calculo de Error Relativo (Criterio de Parada)
double Relative_Error(double theta_g0, double theta_g1, double theta_g2, double theta_0, double theta_1, double theta_2){
    double Norm_act, Norm_ant, err;
    Norm_act = sqrt(pow(theta_g0, 2) + pow(theta_g1, 2) + pow(theta_g2, 2));
    Norm_ant = sqrt(pow(theta_0, 2) + pow(theta_1, 2) + pow(theta_2, 2));
    err    = abs(Norm_act - Norm_ant);
    return err;
}
