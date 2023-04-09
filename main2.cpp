/*
Programa de Regresion Lineal

Compilacion: g++ main2.cpp -o Ejecutable -std=c++11 -lm
Ejecucion: ./Ejecutable
*/

#include <iostream>
#include <unistd.h>
#include <cmath>

//Este es el minimo numero de iteraciones necesarias
//para predecir correctamente los datos que tenemos
#define  EPOCHS 1291
#define alpha 0.05

using namespace std;

double Evaluate(double*, double*, int);
double* Buildx(double*, int, int);
double Sigmoid(double);
int makeThreshold(double);
void makeAllPredicts(int, double*, double*, int, int);
int getiY(double*, int, int);
double Loss(int, double*, double*, int);
double* Gradient(int, double*, double*, int, int);
void Train(int, double*, double*, int, int);

int main(){
    int dims = 4, np = 10;
    double theta[3] = {2.0, -1.0, 3.3};
    double S, Phat;
    double points[] = {1, 11, 6, 1,
                       1, 11, 9, 1,
                       1, 12, 3, 0,
                       1, 12, 7, 1,
                       1, 13, 8, 1,
                       1, 14, 2, 0,
                       1, 15, 5, 0,
                       1, 15, 9, 1,
                       1, 18,10, 0,
                       1, 16, 7, 0};
    double test[] = {1, 12, 6};

    Train(np, points, test, 3, dims);

    S = Evaluate(theta, test,3);
    Phat = Sigmoid(S);
    cout<<"La prediccion para una habitacion 12x6 es: "<<makeThreshold(Phat)<<endl;
    return 0;
}

double Evaluate(double* theta, double* x, int n){
    double s = 0.0;
    for(int i = 0 ; i < n ; i++){
        s += theta[i]*x[i];
    }
    return s;
}

int getiY(double* p, int i, int ne){
    return (int)p[i * ne + 3];
}

double Sigmoid(double S){
    return 1 / (1 + exp(-S));
}

double* Buildx(double* p, int i, int ne){
    return &p[i * ne];
}

int makeThreshold(double p){
    if(p >= 0.5)
        return 1;
    return 0;
}

double Loss(int np, double* p, double* t, int dims){
    int nelemsx = 3;
    double sum = 0.0, eval, phat;
    int y;
    double* x;
    for(int i = 0 ; i < np ; i++){
        x    = Buildx(p, i, dims);
        eval = Evaluate(t, x, nelemsx);
        phat = Sigmoid(eval);
        y    = getiY(p, i, dims);
        sum += y * log(phat) + (1 - y) * log(1 - phat);
    }
    return -sum / (double)np; 
}

double* Gradient(int np, double* p, double* t, int nelems, int dims){
    double sum;
    double* x;
    double* g = new double[nelems];
    for(int j = 0 ; j < nelems ; j++){
        sum = 0.0;
        for(int i = 0 ; i < np ; i++){
            x       = Buildx(p, i, dims);
            sum += (Sigmoid(Evaluate(t, x, nelems)) - getiY(p, i, dims)) * x[j];
        }
        g[j] = sum / (double)np;
    }
    return g;
}

void makeAllPredicts(int np, double* p, double* t, int dims, int cont){
    int nelemsx = 3;
    double* x = NULL;
    double* grad = NULL;
    double eval, phat;
    if(cont%30 == 0){
        for(int i = 0 ; i < np ; i++){
            x = Buildx(p, i, dims);
            eval = Evaluate(t, x, nelemsx);
            phat = Sigmoid(eval);
            cout<<"La prediccion para "<<i<<" es: "<<makeThreshold(phat)<<" debiendo ser: "<<getiY(p, i, dims)<<endl;
        }
        cout<<"La funcion  de perdida da: "<<Loss(np, p, t, dims)<<endl;
        grad = Gradient(np, p, t, nelemsx, dims);
        cout<<"Los valores de gradiente son: "<<grad[0]<<endl;
        cout<<"Los valores de gradiente son: "<<grad[1]<<endl;
        cout<<"Los valores de gradiente son: "<<grad[2]<<endl<<endl<<endl;
    }
}

void ScalarTimesVector(double* v, double* res, double a, int n){
    for(int i = 0 ; i < n ; i++){
        res[i] = a * v[i];
    }
}

void VectorSum(double* v1, double* v2, double* res, int n){
    for(int i = 0 ; i < n ; i++){
        res[i] = v1[i] + v2[i];
    }
}

void Train(int np, double* p, double* t, int nelemsx, int dims){
    //double alpha = 0.05;
    double* grad = NULL;
    for(int i = 0 ; i < EPOCHS ; i++){
        makeAllPredicts(np, p, t, dims, i);
        grad = Gradient(np, p, t, nelemsx, dims);
        ScalarTimesVector(grad, grad, -1*alpha, 3);
        VectorSum(t, grad, t, 3);
        if(i%30 == 0){
            cout<<"Iteracion: "<<i<<endl;
        }
    }
    cout<<"El alpha utilizado fue:"<<alpha<<endl;
    cout<<"Theta0 final: "<<t[0]<<endl;
    cout<<"Theta1 final: "<<t[1]<<endl;
    cout<<"Theta2 final: "<<t[2]<<endl;
}
