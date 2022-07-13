#include<iostream>
#include<fstream>
#include <algorithm>

using namespace std;

int main (int argc, char **argv){  
    bool flag = false;
    int N,K,D,T;
    scanf("%d", &N);       //number of cars
    scanf("%d", &K);       //number of stations
    scanf("%d", &D);       //Distance 
    scanf("%d", &T);       //time limit
    int* p = new int[N];
    int* c = new int[N];
    int* d = new int[K];
    for (int i=0; i < N; i++){
        scanf("%d", &p[i]);
        scanf("%d", &c[i]);
    }
    for (int i=0; i < K; i++){
        scanf("%d", &d[i]);
    }
    int Ts,Cs,Tf,Cf;
    scanf("%d", &Ts);
    scanf("%d", &Cs);
    scanf("%d", &Tf);
    scanf("%d", &Cf);
    int avrg_speed  = T/D;
    if ( avrg_speed < Tf ){
        cout << -1 << endl;
        return 0;
    }

    sort(d, d+K);
    long long int lowest_price = 1000000000;
    int y = (T-Ts*D)/(Tf-Ts);   //minimun distance that the car has to cover on sport mode
    if (y < 0){
        y = 0;
    }
    else if ( (T-Ts*D) % (Tf-Ts) != 0){
        y += 1;
    }
    int x = D - y;              //maximum distance that the car has to cover on economy mode
    int total_gas = y*Cf + x*Cs; //total fuel that the car needs to reach the destination
    double Cavgr = 1.0 * total_gas / D;   //average fuel consumption
    bool found_car = true;
    
    double min_gas = d[0]*Cavgr;
    int min_dist = 0;           

    for (int i = 1; i < K-1; i++){
        if (d[i] - d[i-1] <= d[i+1] - d[i]){
            min_dist = d[i+1] - d[i];
        }
    }
    if ( D - d[K-1] >= min_dist ){
        min_dist = D - d[K-1];
    }

    min_gas = min_dist * Cavgr;


    for ( int i = 0; i < N; i++ ){
        if (min_gas > c[i]) {
            continue;
        }
        else{
            if (p[i] <= lowest_price){
                lowest_price = p[i];
                flag = true;
            }
        }    
    }
    if (flag){
        printf("%d\n", lowest_price);
    }
    else printf("%d\n", -1);


    return 0;
} 