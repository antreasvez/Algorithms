#include <bits/stdc++.h>
#define max_size 100005 
using namespace std;
const int MAX = 200005;

class Graph{
public:
    int M;
    int N;
	long long res;
	long long *bin;
	int *len;
	int *id;
	pair <long long, pair<int, int> > *graph;
	vector< pair<int,int> > *mst; 
    Graph(int M, int N);
    void initialize();
    void sortGraph();
    int root(int x);
    void Union(int x, int y);
    long long kruskal();
    void dfs(int node,int cost,int parent);
};


Graph::Graph(int M, int N){
    this->M = M;
    this->N = N;
	id = new int[MAX];
	graph = new pair<long long, pair<int, int>>[MAX];
	mst = new vector<pair<int,int>>[max_size];
	bin = new long long[400005];
	len = new int[max_size];
    initialize();
}
 
void Graph::sortGraph(){
    sort(graph, graph + M);
}

void Graph::initialize(){
    for(int i = 0;i < MAX; ++i)
        id[i] = i;
    
    for(int i=0; i < 400005; i++)
        bin[i] = 0;
}

int Graph::root(int x){
    while(id[x] != x){
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void Graph::Union(int x, int y){
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

long long Graph::kruskal()
{
    int temp1,temp2;
    long long cost, minCost = 0;
    for(int i = 0; i < M; ++i)
    {
        temp1 = graph[i].second.first;
        temp2 = graph[i].second.second;
        cost = graph[i].first;
        if(root(temp1) != root(temp2))
        {
            minCost += cost;
            mst[temp1].push_back(make_pair(temp2,cost));
            mst[temp2].push_back(make_pair(temp1,cost));
            Union(temp1, temp2);
        }    
    }
    return minCost;
}

void Graph::dfs(int node,int cost,int parent){
        len[node] = 1; 
        for(auto i:mst[node]){
            int next = i.first;
            int temp = i.second;
            if(next != parent){
                dfs(next,temp,node);
                len[node] += len[next]; 
            }
        }
        long long times = ((long long)(N - len[node])) * ((long long)len[node]) ;
        if(times != 0) {
        	bin[cost] = ((long long)(N - len[node])) * ((long long)len[node]);
		}
    }
int main(){
    long long weight, cost, minCost;
    
    int N,M;
    scanf("%d", &N);
    scanf("%d", &M);
    Graph G(M,N);
    int temp1,temp2;
    for(int i = 0; i < M; ++i)
    {
        scanf("%d", &temp1);
        scanf("%d", &temp2);
        scanf("%d", &weight);
        G.graph[i] = make_pair(weight, make_pair(temp1, temp2));
    }
    G.sortGraph();
    minCost = G.kruskal();
    G.dfs(1,0,-1);
    for (int i = 0; i < 400004; i++)
    {
        if(G.bin[i] != 0){
            G.bin[i+1] += G.bin[i]/2;
            G.bin[i] = G.bin[i]%2;
        }
    }
    int length = -1 ;
    for(int i = 400005; i >= 0; i--){
        if(G.bin[i]==1){
            length = i;
            break;
        }
    }
    if(length == -1) {
		printf("%d\n", 0);
	}
    else{
        for(int i = length; i >= 0; i--)
		printf("%d", G.bin[i]);
    }
	printf("\n");
    return 0;
}