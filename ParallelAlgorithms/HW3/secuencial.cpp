#include<bits/stdc++.h>
using namespace std;
const int Nx = 5000;
const int Ny = 5000;
const int iter = 30;
const double cx = 0.4;
const double cy = 0.8;
const double sigmax = 0.2;
const double sigmay = 0.1;
const double PI = acos(-1.0);

const double hx = double(1)/double(Nx - 1);
const double hy = double(1)/double(Ny - 1);

double alpha(double x, double y){
    return x*(x-double(1))*y*(y - double(1)) + double(1);
}

double f(double x, double y){
    return exp(-((x-cx)*(x-cx))/(double(2)*sigmax*sigmax) - ((y-cy)*(y-cy))/(double(2)*sigmay*sigmay))/(double(2)*PI*sigmax*sigmay);
}

int main(){

    double N[Nx][Ny];
    double W[Nx][Ny];
    double C[Nx][Ny];
    double E[Nx][Ny];
    double S[Nx][Ny];

    double b[Nx][Ny];
    double x[Nx][Ny];

    for(int i = 0; i<Nx; i++){
        for(int j = 0; j<Ny; j++){
            
            x[i][j] = 0;

            N[i][j] = 0;
            W[i][j] = 0;
            C[i][j] = 1;
            E[i][j] = 0;
            S[i][j] = 0;
            b[i][j] = 0;
            
            if(i == 0 || j == 0 || i == Nx-1 || j == Ny-1) continue;

            if(j + 1 < Ny){
                N[i][j] = -alpha(double(i)*hx, (double(j) + 0.5)*hy)/(hy*hy);
            }
            if(j - 1 > 0){
                S[i][j] = -alpha(double(i)*hx, (double(j) - 0.5)*hy)/(hy*hy);
            }
            if(i + 1 < Nx){
                E[i][j] = -alpha((double(i) + 0.5)*hx, double(j)*hy)/(hx*hx);
            }
            if(i - 1 > 0){
                W[i][j] = -alpha((double(i) - 0.5)*hx, double(j)*hy)/(hx*hx);
            }

            C[i][j] = ((alpha((double(i) + 0.5)*hx, double(j)*hy) + alpha((double(i) - 0.5)*hx, double(j)*hy))/(hx*hx)) + ((alpha(double(i)*hx, (double(j) + 0.5)*hy) + alpha(double(i)*hx, (double(j) - 0.5)*hy))/(hy*hy));
            b[i][j] = f(double(i)*hx, double(j)*hy);
        }
    }

    double r[Nx][Ny];
    double q[Nx][Ny];
    double p[Nx][Ny];
    double rho = 0;
    double beta = 0;

    for(int i = 0; i<Nx; i++){
        for(int j = 0; j<Ny; j++){
            r[i][j] = C[i][j]*x[i][j] - b[i][j];
            if(j + 1 < Ny){
                r[i][j] += x[i][j+1]*N[i][j];
            }
            if(j - 1 > 0){
                r[i][j] += x[i][j-1]*S[i][j];
            }
            if(i + 1 < Nx){
                r[i][j] += x[i+1][j]*E[i][j];
            }
            if(i - 1 > 0){
                r[i][j] += x[i-1][j]*W[i][j];
            }
        }
    }

    for(int it = 1; it<=iter; it++){
        double oldrho = rho;
        rho = 0;
        for(int i = 0; i<Nx; i++){
            for(int j = 0; j<Ny; j++){
                rho += r[i][j]*r[i][j];
            }
        }

        if(it == 1){
            for(int i = 0; i<Nx; i++){
                for(int j = 0; j<Ny; j++){
                    p[i][j] = r[i][j];
                }
            }
        }
        else{
            beta = rho/oldrho;
            for(int i = 0; i<Nx; i++){
                for(int j = 0; j<Ny; j++){
                    p[i][j] = r[i][j] + beta*p[i][j];
                }
            }
        }
        for(int i = 0; i<Nx; i++){
            for(int j = 0; j<Ny; j++){
                q[i][j] = C[i][j]*p[i][j];
                if(j + 1 < Ny){
                    q[i][j] += p[i][j+1]*N[i][j];
                }
                if(j - 1 > 0){
                    q[i][j] += p[i][j-1]*S[i][j];
                }
                if(i + 1 < Nx){
                    q[i][j] += p[i+1][j]*E[i][j];
                }
                if(i - 1 > 0){
                    q[i][j] += p[i-1][j]*W[i][j];
                }
            }
        }
        double delta = 0;
        for(int i = 0; i<Nx; i++){
            for(int j = 0; j<Ny; j++){
                delta += p[i][j]*q[i][j];
            }
        }
        delta = rho/delta;
        for(int i = 0; i<Nx; i++){
            for(int j = 0; j<Ny; j++){
                x[i][j] = x[i][j] - delta*p[i][j];
                r[i][j] = r[i][j] - delta*q[i][j];
            }
        }
        double resto = 0;
        for(int i = 0; i<Nx; i++){
            for(int j = 0; j<Ny; j++){
                resto += r[i][j]*r[i][j];
            }
        }
        resto = sqrt(resto);
        //cout<<fixed<<setprecision(12)<<resto<<endl;
    }

    return 0;
}