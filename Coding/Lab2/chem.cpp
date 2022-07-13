#include<iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int arr[1500][500];

int chem(int K, int *A[],int curE, int start,int N,int end,int prevE){         //each chemical, we either place it in a barrel or dont,
    if (arr[end][K] == -1){
        if (N-end == K-1){
            return curE;
        }
        else if(K == 1){
            curE = prevE + A[start][N-1];
            return curE;
        }
        else if (end < N){                                                                  // end and start are var to keep in track which chems are in the barrel
            int E1 = A[start][end] + prevE;                                                 // I keep the energy of the barrels that i have already filled with prevE
            int E2 = A[start][end-1] + prevE;
            arr[end][K] = min(chem(K,A,E1,start,N,end+1,prevE),chem(K-1,A,0,end,N,end+1,E2));
            return arr[end][K];
        }
        else {
            return curE;
        }
    }
    else {
        // if( prevE < A[end][start] ){
        //     // int temp = A[end][start];
        //     // A[end][start] = prevE;
        //     return arr[end][K];
        // }
        // else {
        //     return arr[end][K];
        // }
        return arr[end][K];
    }
}

int main(){
    int N,K;
    memset(arr, -1, sizeof(arr)); 
    scanf("%d", &N);
    scanf("%d", &K);

    int** A = new int*[N];
    int temp;
    for (int i = 0; i < N; i++){
        A[i] = new int[N];
        A[i][i] = 0;
        for(int j = i+1; j < N; j++){
            scanf("%d", &temp);
            A[i][j] = temp + A[i][j-1];
        }
    }
    // for (int i = 0; i < N; i++){
    //     for(int j = i+1; j < N; j++){
    //         printf("%d", A[i][j]);
    //         cout << " ";
    //     }
    //     cout << endl;
    // }
    for (int i = 0; i < N; i++){
        for (int j = i+1; j < N; j++){
            for (int t = i+1; t < j; t++){
                A[i][j] += A[t][j];
            }
        }
    }
    // for (int i = 0; i < N; i++){
    //     for(int j = i+1; j < N; j++){
    //         printf("%d", A[i][j]);
    //         cout << " ";
    //     }
    //     cout << endl;
    // }
    int E = chem(K,A,0,0,N,1,0);
    cout << E << endl;
    return 0;
}