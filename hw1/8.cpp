#include <bits/stdc++.h>
#include <unistd.h> // sleep()
#define DIM 5
#define EXP 1126

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
    ifstream data("data/hw1_7_train.dat");
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
    ifstream test("data/hw1_7_test.dat");
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

    // init n
    n = dataset.size();
    double badRate = 0;
    ofstream output("result_8");

// EXP
for(int runtime = 0; runtime < EXP; runtime++){
    // init random info
    srand(runtime + 10000);

    // init w
    double w[DIM];
    for(int i = 0; i < DIM; i++){
        w[i] = 0;
    }

    // init while info
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
    }

    int testsize = testset.size();
    double wrongTime = 0;
    for(int j = 0; j < testsize; j++){
        if(!isRight(w, testset[j])){
            wrongTime ++;
        }
    }
    // cout << (double)(wrongTime / testsize) << endl;
    badRate += (double)(wrongTime / testsize);
    output << (double)(wrongTime / testsize) << '\n';
}
// END OF EXPs
    cout << "Average error rate : " << (double)(badRate / EXP) << endl;
    return 0;
}
