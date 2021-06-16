/*
hw1_15 : naive cycle
*/
#include <bits/stdc++.h>
#define DIM 5

using namespace std;

struct Data{
    double input[DIM];
    int output;
};

vector<Data> dataset;
int n, countn, update = 0;

bool sameSign(double *a, int *b){
    if((*a) * (*b) > 0){
        return true;
    }else{
        return false;
    }
}

bool isRight(double *w, Data data){
    double result = 0;
    for(int i = 0; i < DIM; i++){
        result += w[i] * data.input[i];
    }
    if(sameSign(&result, &data.output)){
        return true;
    }else{
        return false;
    }
}

int main(){
    // Read data
    ifstream data("data/hw1_15_train.dat");
    while(!data.eof()){
        Data temp;
        for(int i = 1; i < DIM; i++){
            data >> temp.input[i];
        }
        data >> temp.output;
        temp.input[0] = 1;
        dataset.push_back(temp);
    }
    data.close();

    // init w
    double w[DIM];
    for(int i = 0; i < DIM; i++){
        w[i] = 0;
    }

    // init while info
    countn = 0;
    int i = 0;
    n = dataset.size();

    // PLA
    while(countn < n){
        if(isRight(w, dataset[i])){
            countn ++;
        }else{
            // correct w
            for(int j = 0; j < DIM; j++){
                w[j] = w[j] + dataset[i].output * dataset[i].input[j];
            }
            countn = 0;
            update++;
        }

        i++;
        i %= n;
    }

    cout << "Total update : " << update << '\n';

    return 0;
}
