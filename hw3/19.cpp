#include <bits/stdc++.h>
#include <unistd.h>
#define DIM 20
#define LR 0.001
#define T 2000

using namespace std;

struct Data{
    double x[DIM + 1];
    int y;
};

vector <Data> data;
vector <Data> test;
int n;

int sign(double x){
    if(x >= 0){
        return 1;
    }else{
        return -1;
    }
}

double theta(double s){
    return (1 / (double)(1 + exp((-1) * s)));
}

double dot(double *w, double *x){
    double ans = 0;
    for(int i = 0; i < DIM + 1; i++){
        ans += w[i] * x[i];
    }
    return ans;
}

void dot_constant(double k, double *x, double *kx){
    for(int i = 0; i < DIM + 1; i++){
        kx[i] = k * x[i];
    }
    return;
}

void static_add(double *weight, double *w_grad){
    for(int i = 0; i < DIM + 1; i++){
        weight[i] += w_grad[i];
    }
}

void gradient_of_Ein(double *weight, double *w_grad){
    for(int i = 0; i < DIM + 1; i++){
        w_grad[i] = 0;
    }
    double yw[DIM + 1];
    for(int i = 0; i < n; i++){
        dot_constant((-1) * data[i].y, weight, yw);
        double temp = theta(dot(yw, data[i].x));
        for(int j = 0; j < DIM + 1; j++){
            w_grad[j] += LR * temp * data[i].x[j] * data[i].y;
        }
    }
    for(int i = 0; i < DIM + 1; i++){
        w_grad[i] /= n;
    }
}

int main(){
    srand(clock());
    ofstream result("result_7"); // plot_7
    // get train
    ifstream train("hw3_train.dat");
    while(!train.eof()){
        Data temp;
        for(int i = 1; i < DIM + 1; i++){
            train >> temp.x[i];
        }
        temp.x[0] = 1;
        train >> temp.y;
        data.push_back(temp);
    }
    train.close();
    // get test
    ifstream infile("hw3_test.dat");
    while(!infile.eof()){
        Data temp;
        for(int i = 1; i < DIM + 1; i++){
            infile >> temp.x[i];
        }
        temp.x[0] = 1;
        infile >> temp.y;
        test.push_back(temp);
    }
    infile.close();
    int n_prime = test.size();

    n = data.size();
    double weight[DIM + 1];
    for(int i = 0; i < DIM + 1; i++){
        weight[i] = 0;
    }
    double w_grad[DIM + 1];
    for(int runtime = 0; runtime < T; runtime++){
        /* 18 and 19 (normal) */
        gradient_of_Ein(weight, w_grad);
        static_add(weight, w_grad);
        /* end of 18 and 19 */

        /* start of 20 (stochastic) */
        // int target = runtime % n;
        // for(int i = 0; i < DIM + 1; i++){
        //     w_grad[i] = 0;
        // }
        // double yw[DIM + 1];
        // dot_constant((-1) * data[target].y, weight, yw);
        // double temp = theta(dot(yw, data[target].x));
        // for(int j = 0; j < DIM + 1; j++){
        //     w_grad[j] += LR * temp * data[target].x[j] * data[target].y;
        // }
        // static_add(weight, w_grad);
        /* end of 20 */

        /* start of handwritten 7 */
        double Ein = 0;
        for(int i = 0; i < n; i++){
            if(sign(dot(weight, data[i].x)) != data[i].y){
                Ein ++;
            }
        }
        Ein /= n;
        result << runtime << ' ' << Ein << endl;
        /* end of handwritten 7 */
        /* start of handwritten 8 */
        // double Eout = 0;
        // for(int i = 0; i < n_prime; i++){
        //     if(sign(dot(weight, test[i].x)) != test[i].y){
        //         Eout ++;
        //     }
        // }
        // Eout /= n_prime;
        // result << runtime << ' ' << Eout << endl;
        /* end of handwritten 8 */
    }
    double Eout = 0;
    for(int i = 0; i < n_prime; i++){
        if(sign(dot(weight, test[i].x)) != test[i].y){
            Eout ++;
        }
    }
    Eout /= n_prime;
    printf("Eout is %lf\n", Eout);
    for(int i = 0; i < DIM + 1; i++){
        printf("%lf ", weight[i]);
    }
    printf("\n");
    printf("%d\n", n);
    return 0;
}
