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
