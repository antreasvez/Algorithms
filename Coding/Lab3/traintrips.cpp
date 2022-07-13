#include<iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std; 
int mem[100000000];
string traintrip(int *d, int s, int i, int N, int prev){
    if (s < d[i] && i < N-1){
        return traintrip(d,s,i+1, N, prev);
    }
    else if (s < d[i]){
        return "NO";
    }
    int temp = (s-prev)/d[i];

    if ((s-prev)%d[i] == 0){
        mem[s] = 1;
        mem[s-prev] = 1;
        return "YES";
    }
    else {
        for (int t = 0; t <= temp; t++){
            mem[t*d[i]] = 1;
            mem[t*d[i]+prev] = 1;
            if (mem[s-t*d[i]]-prev != 1){
                if (s-t*d[i]-prev == 0){
                    mem[s] = 1;
                    mem[s-prev] = 1;
                    return "YES";
                }
                else if (s-t*d[i] > 0 && i < N-1) {
                    if (traintrip(d,s,i+1, N, t*d[i]+prev) == "YES"){
                        mem[s-prev] = 1;
                        return "YES";
                    }
                }
            }
            else
            {
                return "YES";
            }
        }
    }
    return "NO";
}




int main (){
    memset(mem, -1, sizeof(mem));
    int  N,Q,*d,*s;
    scanf("%d", &N);
    scanf("%d", &Q);
    d = new int[N];
    s = new int[Q];

    for (int i = 0; i < N; i++){
        scanf("%d", &d[i]);
    }
    int maxS = 0;
    for (int i = 0; i < Q; i++){
        scanf("%d", &s[i]);
        if (maxS < s[i]) maxS = s[i];
    }
    traintrip(d,maxS, 0, N, 0);
    
    for (int i = 0; i < Q; i++){
        traintrip(d,s[i], 0, N, 0);
    }

    return 0;
}