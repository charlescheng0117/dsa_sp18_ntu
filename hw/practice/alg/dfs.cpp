// reference -> https://www.geeksforgeeks.org/iterative-depth-first-traversal/
// An Iterative C++ program to do DFS traversal from
// a given source vertex. DFS(int s) traverses vertices
// reachable from s.
#include <iostream>
#include <list>
#include <vector>
#include <stack>
//#include<bits/stdc++.h>
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
    void DFS(int s);  
};
 
// prints all not yet visited vertices reachable from s
void Graph::DFS(int s)
{
    vector<bool> visited(N, false); // 

    stack<int> stack;   
    stack.push(s); // Push the current source node.
 
    while (!stack.empty())
    {
        // Pop a vertex from stack and print it
        s = stack.top();
        cout << s << " "; 
        
        if (!visited[s])			// Stack may contain same vertex twice. So
        {							// we need to print the popped item only
            //cout << s << " ";		// if it is not visited.
            visited[s] = true;
        }        
        stack.pop(); 
 
        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        //list<int>::const_iterator i;
        /*
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i])
                stack.push(*i);
         */
        for (Edge e : adj[s]) {
            if (!visited[e.v]) {
                stack.push(e.v);
            }
        }
    }
    cout << "\n";
}
 
// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    int N;
    scanf("%d", &N);
    printf("N = %d\n", N);

    int M;
    scanf("%d", &M);
    printf("M = %d\n", M);

    Graph g(N);
    int v, w, d;

    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d", &v, &w, &d);
        printf("%d %d %d\n", v, w, d);
        g.addEdge(v, w, d); 
    }

    int s;
    scanf("%d", &s);
    printf("s = %d\n", s);
 
    cout << "Following is Depth First Traversal "
         << "(starting from vertex " << s << " ) \n";

    g.DFS(s);
 
    return 0;
}
