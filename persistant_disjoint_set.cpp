struct disjoint_set{
    vector<int> par, size;
    vector<pii> par_log, sz_log;

    disjoint_set (int n) : size(n, 1), par(n){
        iota(par.begin(), par.end(), 0);
    }

    int getRoot (int idx){
        return idx == par[idx] ? idx : getRoot(par[idx]);
    }

    bool mrg (int x, int y){
        x = getRoot(x);
        y = getRoot(y);
        if(x == y) return false;
        if( size[x] > size[y] ) swap(x,y);

        par_log.emplace_back(x, par[x]);
        sz_log.emplace_back(y, size[y]);

        par[x] = y;
        size[y] += size[x];

        return true;
    }

    void undo (){
        pii par_bk = par_log.back();
        par[par_bk.first] = par_bk.second;

        pii sz_bk = sz_log.back();
        size[sz_bk.first] = sz_bk.second;

        par_log.pop_back();
        sz_log.pop_back();
    }
};
