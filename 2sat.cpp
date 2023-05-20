struct tsat {
    int n;
    vector<vector<int>> impl;
    tsat(int vars) {
        n = vars;
        impl.assign(n * 2, vector<int>(0));
    }
    void disjunction(int a, int na, int b, int nb) {
        int a_true = a * 2 + na, a_false = a * 2 + (!na);
        int b_true = b * 2 + nb, b_false = b * 2 + (!nb);
        impl[a_false].pb(b_true);
        impl[b_false].pb(a_true);
    }
    vector<int> vis, order;
    void dfs(int idx) {
        vis[idx] = 1;
        for(int& e : impl[idx]) {
            if(vis[e] == 0) {
                dfs(e);
            }
        }
        order.pb(idx);
    }
    vector<int> ids;
    void label(int idx, int id) {
        ids[idx] = id;
        for(int& e : impl[idx]) {
            if(ids[e] == -1) {
                label(e, id);
            }
        }
    }
    vector<int> solve() {
        order.clear();
        vis.assign(n * 2, 0);
        for(int i = 0; i < 2 * n; i++) {
            if(vis[i] == 0) {
                dfs(i);
            }
        }

        int comp_cnt = 0;
        ids.assign(n * 2, -1);
        for(int idx : order) {
            if(ids[idx] == -1) {
                label(idx, comp_cnt);
                comp_cnt++;
            }
        }

        for(int i = 0; i < n * 2; i += 2) {
            if(ids[i] == ids[i + 1]) {
                return {-1};
            }
        }

        int ptr = 0;
        vector<int> sol(comp_cnt, -1);
        while(ptr < sz(order)) {
            if(sol[ids[order[ptr]]] != -1) {
                ptr++;
                continue;
            }
            sol[ids[order[ptr]]] = 1;
            for(int i = ptr; i < sz(order) && ids[order[i]] == ids[order[ptr]]; i++) {
                sol[ids[order[i] ^ 1]] = 0;
            }
        }

        vector<int> ret(n, -1);
        for(int i = 0; i < n; i++) {
            if(sol[ids[i * 2]] == 1) {
                ret[i] = 1;
            } else {
                ret[i] = 0;
            }
        }
        return ret;
    }
};
