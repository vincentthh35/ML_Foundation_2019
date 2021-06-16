/*
hw1_16 : fixed, pre-determined random cycle
Change the update rule
REPEAT 2000 times
*/
#include <bits/stdc++.h>
#include <unistd.h> // sleep()
#define DIM 5
#define EXP 2000

using namespace std;

struct Data{
    double input[DIM];
    int output;
};

vector<Data> dataset, testset;
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

bool isBetter(double *w, double *wprime){
    int countw = 0, countwprime = 0;
    for(int i = 0; i < n; i++){
        if(!isRight(w, dataset[i])){
            countw++;
        }
        if(!isRight(wprime, dataset[i])){
            countwprime ++;
        }
    }
    if(countw > countwprime){
        return true;
    }else{
        return false;
    }
}

int main(){
    // Read data
    ifstream data("data/hw1_18_train.dat");
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

    // Read test data
    ifstream test("data/hw1_18_test.dat");
    while(!test.eof()){
        Data temp;
        for(int i = 1; i < DIM; i++){
            test >> temp.input[i];
        }
        test >> temp.output;
        temp.input[0] = 1;
        testset.push_back(temp);
    }
    test.close();

    // init stat
    int stat[100];
    for(int i = 0; i < 100; i++){
        stat[i] = 0;
    }

    // init n
    n = dataset.size();
    int totalcount = 0;
    ofstream result("result");
    double badRate = 0;
// EXP
for(int runtime = 0; runtime < EXP; runtime++){
    // init random info
    srand(runtime + 10000);
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

    // init w and best
    double bestw[DIM];
    double w[DIM];
    for(int i = 0; i < DIM; i++){
        w[i] = 0;
        bestw[i] = 0;
    }

    // init while info
    int i = 0;
    countn = 0;
    int update = 0;

    // Pocket PLA
    while(update < 100){
        // check if it is wrong
        int next = rand() % n;
        if(!isRight(w, dataset[next])){
            // correct w
            for(int j = 0; j < DIM; j++){
                w[j] = w[j] + dataset[next].output * dataset[next].input[j];
            }
            update ++;
        }
        //check if it is better
        if(isBetter(bestw, w)){
            for(int j = 0; j < DIM; j++){
                bestw[j] = w[j];
            }
        }
        // cout << "update : " << update << '\n';
        i++;
        i %= n;
    }

    int testsize = testset.size();
    double wrongTime = 0;
    for(int j = 0; j < testsize; j++){
        if(!isRight(bestw, testset[j])){
            wrongTime ++;
        }
    }
    badRate += (double)(wrongTime / testsize);
    cout << "The " << runtime << "-th EXP : wrongTime : " << wrongTime << '\n';
    cout << "The " << runtime << "-th EXP : bad rate : " << ((double)wrongTime / (double)testsize) << '\n';
    // result << update << endl;
    // stat[update] ++;
    // totalcount += update;
    // cout << runtime << "-th for loop, update : " << update << endl;
    // update = 0;
}
// END OF EXPs
    // cout << "Total update : " << update << '\n';
    // cout << "Avg. update : " << (totalcount / 1126) << '\n';
    cout << "Avg. wrong rate : " << (double)(badRate / EXP) << '\n';
    return 0;
}
