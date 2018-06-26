// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices 
// reachable from s.
#include <iostream>
#include <list>
#include <vector>
#include <queue>
 
using namespace std;

struct Edge {
    int v;        // to vertex v
    int dis; // vertex's distance

    bool operator< (const Edge& e) const {
        return dis < e.dis;
    }

    Edge () {}

    Edge (int new_v, int new_dis) {
        v = new_v;
        dis = new_dis;
    }
};

// This class represents a directed graph using
// adjacency list representation
class Graph {
    int N;    // No. of vertices
    vector< vector<Edge> > adj; // adjacency list
public:
    Graph(int new_N) { // constructor
        N = new_N;
        //vector< vector<Edge> > tmp(N, vector<Edge>(0));
        //adj = tmp;
        adj = vector< vector<Edge> >(N);
    } 
    // function to add an edge to graph
    void addEdge(int v, int w, int dis) {
        adj[v].push_back( Edge(w, dis) );
    }
 
    // prints BFS traversal from a given source s
    void BFS(int s);  
};
 
void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    vector<bool> visited(N, false);
 
    // Create a queue for BFS
    queue<int> q;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    q.push(s);
 
    while(!q.empty())
    {
        // Dequeue a vertex from queue and print it
        s = q.front();
        cout << s << " ";
        q.pop();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited, 
        // then mark it visited and enqueue it
        /*
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
        */
        for (Edge e : adj[s])
        {
            if (!visited[e.v])
            {
                visited[e.v] = true;
                q.push(e.v);
            }
        }
    }
    cout << "\n";
}
 
// Driver program to test methods of graph class
int main() {
    // Create a graph given in the above diagram
    int N;
    scanf("%d", &N);
    printf("N = %d\n", N);

    Graph g(N);
    int v, w, d;

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &v, &w, &d);
        printf("%d %d %d\n", v, w, d);
        g.addEdge(v, w, d); 
    }

    int s;
    scanf("%d", &s);
    printf("s = %d\n", s);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex " << s << " ) \n";

    g.BFS(s);
 
    return 0;
}
