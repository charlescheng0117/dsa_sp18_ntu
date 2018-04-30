#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>

using namespace std;

typedef vector<int> Edges;

struct Edge {
    int v1;
    int v2;

    Edge () {}

    Edge (int i, int j) {
        v1 = i;
        v2 = j;
    }
    
};

class Graph {
public:    
    vector< vector<int> > edge_list;
    unordered_set<int> V;
    unordered_map<int, Edges> E; //

    Graph () {}

    void insert (int v1, int v2) {
        auto search_v1 = V.find(v1);
        auto search_v2 = V.find(v2);

        if (search_v1 == V.end()) {
            V.insert(v1);
            Edges e = {v2};
            E.insert( {v1, e} );
        } else {
            auto got = E.find(v1);
            Edges E1 = got->second;

            auto search_v2 = find(E1.begin(), E1.end(), v2);
            
            if (search_v2 == E1.end()) {
                got->second.push_back(v2);
            }

        }

        if (search_v2 == V.end()) {
            V.insert(v2);
            Edges e = {v1};
            E.insert( {v2, e} );
        } else {
            auto got = E.find(v2);
            Edges E2 = got->second;
 
            auto search_v1 = find(E2.begin(), E2.end(), v1);

            if (search_v1 == E2.end()) {
                got->second.push_back(v1);
            }
        
        }
        
    }

    void print() {
        // print V
        for (unordered_set<int>::iterator it = V.begin(); it != V.end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
        
        for (unordered_map<int, Edges>::iterator it = E.begin(); it != E.end(); ++it) {
            int v = it->first;
            Edges e = it->second;
            
            printf("%d: ", v);
            int len = e.size();
            for (int i = 0; i < len; ++i) {
                printf("%d ", e[i]);
            }
            printf("\n");

        }
        printf("\n");
    }

};

unordered_set<int> bfs(Graph& g) {
    unordered_set<int> V = g.V;
    unordered_map<int, Edges> E = g.E;
    int start_v = *(V.begin());

    queue<int> q;
    q.push(start_v);

    unordered_set<int> seen;
    while (!q.empty()) {
        int cur_v = q.front();
        q.pop();
        


        // visit cur_v
        if (seen.find(cur_v) == seen.end()) {
            seen.insert(cur_v);
            printf("%d ", cur_v);
        }

        Edges end_vertices = E[cur_v];
        /*
        for (int i = 0; i < end_vertices.size(); ++i) {
            printf("%d ", end_vertices[i]);
        }
        printf("\n");
        */
       
        // push all it's end_v
        for (auto end_v : end_vertices ) {
            if (seen.find(end_v) == seen.end())
                q.push(end_v);
        } 
        

    }
    printf("\n");

    return seen;
}

void test() {

    unordered_map<int, string> map = { {1, "CMU"}, {2, "UCBerkeley"}, {3, "Stanford"} };
    for (auto pair : map ) {
        printf("%d, %s\n", pair.first, pair.second.c_str());
    }
    printf("\n");

    string school = map[1];

    printf("school: %s\n", school.c_str());

}


int main(int argc, char *argv[]) {
    
    Graph g;
    
    int n, m;

    fscanf(stdin, "%d %d", &n, &m);
    if ( (n - m) != 1) {
        printf("no\n");
        return 1;
    }

    int uj, vj;
    for (int i = 0; i < m; ++i) {
        fscanf(stdin, "%d %d", &uj, &vj);
        g.insert(uj, vj); 
    }

    g.print();

    unordered_set<int> seen = bfs(g);


    if (seen.size() != n) {
        printf("no\n");
    } else {
        printf("yes\n");
    }
    
    return 0;
}
