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

