#include <bits/stdc++.h> 
#include <iostream>

using namespace std; 
bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.first < b.first); 
} 
int knapSack(int W, vector<pair<int,int>> ar, int n, int **K){ 
    int i, w; 
    for (i = 0; i <= n; i++){ 
        for (w = 0; w <= W; w++){ 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (K[i-1][w] == K[i-1][w-1]){
                if (ar[i - 1].first < w) {
                    if (K[i][w-1] > ar[i - 1].second + K[i - 1][w - ar[i - 1].first]){
                        if (K[i - 1][w - ar[i - 1].first] == K[i - 1][w - ar[i - 1].first-1]){
                            K[i][w] = K[i][w-1];
                        }
                        else K[i][w] = ar[i - 1].second + K[i - 1][w - ar[i - 1].first];
                    }
                    else {  
                        K[i][w] = ar[i - 1].second + K[i - 1][w - ar[i - 1].first];
                    }
                }
                else if (ar[i - 1].first == w){
                    K[i][w] = ar[i - 1].second + K[i - 1][w - ar[i - 1].first];
                } 
                else
                    K[i][w] = K[i - 1][w]; 
            }
            else {
                if (ar[i - 1].first == w){
                    K[i][w] = min(ar[i-1].second, K[i-1][w]);
                    if (ar[i - 1].second > K[i-1][w] ){
                        for (int j = w+1; j < W; j++){
                            if (j % ar[i-1].first == 0) {
                                if (K[i-1][j] == K[i-1][j-1]){
                                    K[i][j] = ar[i - 1].second + K[i - 1][j - ar[i - 1].first];
                                    break;
                                }
                                else {
                                    K[i][j] = min( ar[i - 1].second + K[i - 1][j - ar[i - 1].first] , K[i - 1][j] ); 
                                    if (K[i][j] == ar[i - 1].second + K[i - 1][j - ar[i - 1].first]) break;
                                }
                            }
                            else {
                                K[i][j] = K[i - 1][j];
                            }
                            w++;
                        }
                    }

                }
                else if (ar[i - 1].first < w) {
                    if (K[i - 1][w - ar[i - 1].first] != 0){
                        K[i][w] = min( ar[i - 1].second + K[i - 1][w - ar[i - 1].first] , K[i - 1][w] ); 
                    }
                    else {  K[i][w] = K[i - 1][w]; }
                }
                else
                    K[i][w] = K[i - 1][w]; 
            }
        } 
    } 
    return K[n][W]; 
} 

int create_arr(int** &K,vector<pair<int,int>> ar,int N){

    int n = ar.size();
    K = new int*[n+1];
    int wt = 0;

    for (int i = 0; i < n; i++){
        wt += ar[i].first;
    }
    for (int i = 0; i <= n; i++){
        K[i] = new int[wt+1];
    }
    knapSack(wt, ar, n, K);
    return wt;
}

void create_price(int *price, vector<pair<int,int>> ar1,vector<pair<int,int>> ar2,vector<pair<int,int>> ar3,int N,int **Ka,int **Kb,int **Kc,int Wa, int Wb, int Wc){
    int n1 = ar1.size();
    int n2 = ar2.size();
    int n3 = ar3.size();
    int tempA = Wa;
    int tempB = Wb;
    int tempC = Wc;
    N = max(N,Wa);
    N = max(N,Wb);
    N = max(N,Wc);
    for (int i = N; i > 0; i--){
        if (i <= Wa){
            if (Ka[n1][i] != Ka[n1][i-1] && Ka[n1][tempA] > Ka[n1][i]){
                tempA = i;
            }
        }
        if (i <= Wb){
            if (Kb[n2][i] != Kb[n2][i-1] && Kb[n2][tempB] > Kb[n2][i]){
                tempB = i;
            }
        }
        if (i <= Wc){
            if (Kc[n3][i] != Kc[n3][i-1] && Kc[n3][tempC] > Kc[n3][i]){
                tempC = i;
            }
        }
        if (i > Wa ){
            price[i] = 0;
            continue;
        }
        if (i > Wb ){
            price[i] = 0;
            continue;
        }
        if (i > Wc ){
            price[i] = 0;
            continue;
        }
        price[i] = Ka[n1][tempA] + Kb[n2][tempB] + Kc[n3][tempC];
    }
}

int main(){
    int N,M;
    scanf("%d", &N);
    scanf("%d", &M);
    vector< pair <int, int> > A1;
    vector< pair <int, int> > B1;
    vector< pair <int, int> > C1;
    vector< pair <int, int> > A2;
    vector< pair <int, int> > B2;
    vector< pair <int, int> > C2;
    vector< pair <int, int> > A3;
    vector< pair <int, int> > B3;
    vector< pair <int, int> > C3;

    int temp;
    char c;
    int A,P;
    int count = 0;
    for (int i = 0; i < M; i++){
        scanf("%d", &temp);
        scanf("%c", &c);
        scanf("%d", &A);
        scanf("%d", &P);
        if (temp == 1){
            if (c == 'A'){
                A1.push_back( make_pair(A,P));

            }
            else if (c == 'B'){
                B1.push_back( make_pair(A,P));
            }
            else if (c == 'C'){
                C1.push_back( make_pair(A,P));
            }
            
        }
        else if (temp == 2){
            if (c == 'A'){
                A2.push_back( make_pair(A,P));
            }
            else if (c == 'B'){
                B2.push_back( make_pair(A,P));
            }
            else if (c == 'C'){
                C2.push_back( make_pair(A,P));
            }
            
        }
        else if (temp == 3){
            if (c == 'A'){
                A3.push_back( make_pair(A,P));
            }
            else if (c == 'B'){
                B3.push_back( make_pair(A,P));
            }
            else if (c == 'C'){
                C3.push_back( make_pair(A,P));
            }
            
        }
    }
    int** Ka1; 
    int** Kb1;
    int** Kc1;
    int** Ka2;
    int** Kb2;
    int** Kc2;
    int** Ka3;
    int** Kb3;
    int** Kc3;
    sort(A1.begin(), A1.end(), sortbysec); 
    sort(B1.begin(), B1.end(), sortbysec); 
    sort(C1.begin(), C1.end(), sortbysec); 
    sort(A2.begin(), A2.end(), sortbysec); 
    sort(B2.begin(), B2.end(), sortbysec); 
    sort(C2.begin(), C2.end(), sortbysec); 
    sort(A3.begin(), A3.end(), sortbysec); 
    sort(B3.begin(), B3.end(), sortbysec); 
    sort(C3.begin(), C3.end(), sortbysec); 
    int Wa1 = create_arr(Ka1,A1,N);
    int Wb1 = create_arr(Kb1,B1,N);
    int Wc1 = create_arr(Kc1,C1,N);
    int W1 = min(Wa1,Wb1);
    W1 = min(W1,Wc1);
    int Wa2 = create_arr(Ka2,A2,N);
    int Wb2 = create_arr(Kb2,B2,N);
    int Wc2 = create_arr(Kc2,C2,N);
    int W2 = min(Wa2,Wb2);
    W2 = min(W2,Wc2);
    int Wa3 = create_arr(Ka3,A3,N);
    int Wb3 = create_arr(Kb3,B3,N);
    int Wc3 = create_arr(Kc3,C3,N);
    int W3 = min(Wa3,Wb3);
    W3 = min(W3,Wc3);
    int* price1 = new int[N+1];
    int* price2 = new int[N+1];
    int* price3 = new int[N+1];
    if (W1+W2+W3 < N){
        printf("%d\n", -1);
        return 0;
    }
    create_price(price1,A1,B1,C1,N,Ka1,Kb1,Kc1,Wa1,Wb1,Wc1);
    create_price(price2,A2,B2,C2,N,Ka2,Kb2,Kc2,Wa2,Wb2,Wc2);
    create_price(price3,A3,B3,C3,N,Ka3,Kb3,Kc3,Wa3,Wb3,Wc3);
    price1[0] = 0;
    price2[0] = 0;
    price3[0] = 0;
    int min = price1[W1] + price2[W2] + price3[W3];
    for (int i = 0; i <= W1; i++){
        for (int j = 0; j <= W2; j++){
            if (N-i-j <= W3 && N-i-j >= 0){
                int temp =  price1[i] + price2[j] + price3[N-i-j];
                if (min > temp) {
                    min = temp;
                    }
            }
        }
    }
    printf("%d\n", min);
    return 0;
}