#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<stdint.h>
#include<stack>
#include<map>
#include<queue>
#include<functional>

#define MAX64 0x7fffffffffffffff 
#define MAX32 0x7fffffff
#define ll int_fast64_t
#define int int_fast32_t

using namespace std;

struct unweighted_graph{
    vector<vector<int>> adj;

    unweighted_graph(int m_size) : adj(m_size){}

    void one_way_connect(int from, int to){
        adj[from].push_back(to);
    }

    void biconnect(int from, int to){
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
};

vector<int> topo_sort(vector<vector<int>>& adj, int root = 0){
    vector<int> ans;
    vector<bool> searched(adj.size(), false);
    function<void(int)> bfs = [&](int idx){
        searched[idx] = true;
        for(int e : adj[idx]){
            if(searched[e] == true) continue;
            bfs(e);
        }
        ans.push_back(idx);
    };
    bfs(root);

    return ans;
}
