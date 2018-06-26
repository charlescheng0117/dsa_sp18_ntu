#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>    // std::fill
#include <limits>

using namespace std;

typedef long long ll;

struct Edge {
    int v; // THIS vertex to v
    ll d;

    Edge() {}
    Edge(int new_v, ll new_d) {
        v = new_v;
        d = new_d;
    }
    
    void print() {
        printf("v: %d, d: %lld\n", v, d);
    }
};

struct edge_greater {
    bool operator() (Edge e1, Edge e2) {
        return e1.d > e2.d;
    }
};


ll inf = numeric_limits<ll>::max();

vector<bool> vis;

void dijkstra(int a, int N, vector<ll>& dis, vector< vector<Edge> >& edges) {
    // a: source
    // N: num vertices
    // edges: graph
    priority_queue<Edge, vector<Edge>, edge_greater> pq;
    fill(vis.begin(), vis.end(), false);
    fill(dis.begin(), dis.end(), inf);

    dis[a] = 0;
    pq.push( Edge(a, 0) );
    int v; // for starting vertex

    // i: for every starting vertex in edges(edges is actually the graph)
    for (int i = 0; i < N; ++i) {
        v = pq.top().v;
        while (vis[v]) {
            pq.pop();
            v = pq.top().v;
        }
    
        vis[v] = true;

        for (Edge e : edges[v]) {
            if ( (!vis[e.v]) && (dis[e.v] > dis[v] + e.d) ) {
                dis[e.v] = dis[v] + e.d;
                pq.push( Edge(e.v, dis[e.v]) );
            }
        
        }
    
    }

}

int main(int argc, char** argv) {

    int T;
    scanf("%d", &T);

    for (int t = 0; t < T; ++t) {
    
        int N, M;
        scanf("%d %d", &N, &M);

        int A, B;
        scanf("%d %d", &A, &B);

        vector<ll> dis1(N);
        vector<ll> dis2(N);
        vis = vector<bool>(N);
    
        vector< vector<Edge> > graph(N, vector<Edge>(0) );
        vector< vector<Edge> > reverse(N, vector<Edge>(0) );

        int Ai, Bi;
        ll Ki;
        for (int i = 0; i < M; ++i) {
            scanf("%d %d %lld", &Ai, &Bi, &Ki);
            
            graph[Ai].push_back( Edge(Bi, Ki) ); // edge from Ai to Bi with cost Ki
            reverse[Bi].push_back( Edge(Ai, Ki) ); // reverse graph
        }
        
        dijkstra(A, N, dis1, graph);
        dijkstra(B, N, dis2, reverse);
    
        ll ans = inf;
        ll len = 0;
        for (int i = 0; i < N; ++i) {
            vector<Edge> edges = graph[i];
            for (Edge e : edges) {
                len = dis1[i] + dis2[e.v] + e.d;
                if ( len != dis1[B] && len < ans) {
                    ans = len;
                }
            }
        
        }
        
        printf("%lld\n", ans - dis1[B]);
    
    }

}
