#include<iostream>
#include<fstream>
#include <algorithm>
#include <vector> 
using namespace std;

struct portals
{
    int a;
    int b;
    int w;
};

bool increasing(portals p1, portals p2){
    return p1.w < p2.w;
}

class Graph{
    int N;
    vector<int> *g;
    int *Morty_belongs;
    bool *visited;
 public:
    Graph(int N);
    bool dfs (int N, int M, portals P[],int mid,int c[]);
    void DFSutil (int i, int component);
    void create_edges(int mid, int M, portals P[]);
};
Graph::Graph(int N){
    this->N = N;
    g = new vector<int>[N+1];
    Morty_belongs = new int[N+1];
    visited = new bool[N+1];
    for (int i =0; i < N+1; i++){
        Morty_belongs[i] = 0;
        visited[i] = false;
    }
}
void Graph::create_edges(int mid, int M, portals P[]){
    for (int i=mid; i < M; ++i){
        g[P[i].b].push_back(P[i].a);
        g[P[i].a].push_back(P[i].b);
    }
}

void Graph::DFSutil (int i, int component){
    int j = 0; 
    for (j; j < g[i].size(); j++){
        int temp = g[i][j];
        if (visited[temp] == false){
            Morty_belongs[temp] = component;
            visited[temp] = true;
            DFSutil(temp,component);
        }
    }
}
bool Graph::dfs (int N, int M, portals P[],int mid,int c[]){
    int component=0;
    create_edges(mid,M,P);


    for (int i=1; i < N+1; i++){
        if (!visited[i]){
            component += 1;
            Morty_belongs[i] = component;
            visited[i] = true;
            DFSutil(i,component);

        }
    }
    for (int i=1; i < N+1; i++){
        if (Morty_belongs[c[i]] == Morty_belongs[i]){
            continue;
        }
        return false;      
    }
    return true;
}

int main (int argc, char **argv){
    int N,M;
    scanf("%d", &N);
    scanf("%d", &M);
    int* c = new int[N+1];
    int a,b,w;

    portals* P = new portals[M];

    for (int i=1; i < N+1; i++){
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < M; i++){
        scanf("%d", &P[i].a);
        scanf("%d", &P[i].b);
        scanf("%d", &P[i].w);
    }
    sort(P,P+M,increasing);
    int r = M-1;
    int l = 0;
    int mid;
    int flag;  //if binary search ends with a graph that is not connective, then we have to use mid-1
    while (r>=l){
        mid = l + (r - l) / 2; 
        Graph G(N);
        if (!G.dfs(N,M,P,mid,c)){
            flag = 1;
            r = mid - 1;
            continue;
        }
        else {
            flag = 0;
            l = mid + 1;
            continue;
        }
    }
    printf("%d\n", P[mid-flag].w);
    return 0;
}