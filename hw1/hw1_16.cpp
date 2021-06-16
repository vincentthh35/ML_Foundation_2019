/*
hw1_16 : fixed, pre-determined random cycle
REPEAT 2000 times
*/
#include <bits/stdc++.h>
#include <unistd.h> // sleep()
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



    // init n
    n = dataset.size();
    int totalcount = 0;
// 2000 EXP
for(int runtime = 0; runtime < 2000; runtime++){
    // init random info
    srand((unsigned)time(NULL));
    bool picked[n];
    int randOrder[n];
    for(int i = 0; i < n; i++){
        picked[i] = false;
    }
    int pickcount = 0, next;
    while(pickcount < n){
        next = rand() % n;
        while(picked[next] == true){
            next = rand() % n;
        }
        picked[next] = true;
        randOrder[pickcount] = next;
        pickcount ++;
    }

    // init w
    double w[DIM];
    for(int i = 0; i < DIM; i++){
        w[i] = 0;
    }

    // init while info
    int i = 0;
    countn = 0;

    // PLA
    while(countn < n){
        if(isRight(w, dataset[randOrder[i]])){
            countn ++;
        }else{
            // correct w
            for(int j = 0; j < DIM; j++){
                w[j] = w[j] + dataset[randOrder[i]].output * dataset[randOrder[i]].input[j];
            }
            countn = 0;
            update++;
        }

        i++;
        i %= n;
    }
    totalcount += update;
    // cout << runtime << "-th for loop, update : " << update << endl;
    update = 0;
    sleep(1);
}
// END OF 2000 EXPs
    // cout << "Total update : " << update << '\n';
    cout << "Avg. update : " << (float)(totalcount / 2000) << '\n';
    return 0;
}
