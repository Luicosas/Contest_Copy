#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define pb push_back
#define sz(x) (int)(x.size())
#define itr(x) x.begin(), x.end()
#define prv(x) for(auto& i : x) cout << i << " "; cout << "\n";
#define debug(...) cerr << #__VA_ARGS__ << " : "; for(auto& i : {__VA_ARGS__}) cerr << i << " "; cerr << "\n";

vector<array<int,2>> locs;
vector<int> dis, calc, caps;
vector<vector<array<int,3>>> adj;

void cdis(int source) {
    deque<array<int,2>> que(1, {source, 0});
    while(sz(que) > 0) {
        int idx = que[0][0], d = que[0][1];
        que.pop_front();

        if(dis[idx] <= d) {
            continue;
        }
        dis[idx] = d;

        for(auto e : adj[idx]) {
            if(caps[e[1]] > 0) {
                que.push_back({e[0], d + 1});
            }
        }
    }
}

int augment(int idx, int cap, int sink) {
    if(idx == sink) {
        return cap;
    }

    while(calc[idx] < sz(adj[idx])) {
        auto& e = adj[idx][calc[idx]];
        if(dis[idx] >= dis[e[0]]) {
            calc[idx]++;
            continue;
        }
        if(caps[e[1]] == 0) {
            calc[idx]++;
            continue;
        }
        int aug = augment(e[0], min(cap, caps[e[1]]), sink);
        if(aug == 0) {
            calc[idx]++;
            continue;
        }
        caps[e[1]] -= aug;
        caps[e[2]] += aug;
        return aug;
    }
    return 0;
}

void dinic(int source, int sink) {
    while(true) {
        dis.assign(sz(adj), INT_MAX);
        cdis(source);

        if(dis[sink] == INT_MAX) {
            return;
        }

        calc.assign(sz(adj), 0);
        while(augment(source, INT_MAX, sink));
    }
}

vector<int> visx, visy;
void bilabel(int idx) {
    visy[idx] = 1;

    for(auto& e : adj[idx]) {
        int xidx = e[0] - sz(locs);
        if(e[0] < sz(locs) * 2 && visx[xidx] == 0 && caps[e[1]] == 1) {
            visx[xidx] = 1;
            for(auto& e : adj[e[0]]) {
                if(caps[e[1]] == 1 && !visy[e[0]]) {
                    bilabel(e[0]);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> A(n, vector<int>(m, 0));
    for(auto& v : A) {
        for(auto& i : v) {
            char c;
            cin >> c;
            i = (c - '0');
        }
    }

    vector<vector<array<int,2>>> lb(n, vector<array<int,2>>(m, {-1, -1}));
    for(int y = 0; y < n; y++) {
        for(int x = 0; x < m; x++) {
            if(A[y][x]) {
                lb[y][x] = {sz(locs), sz(locs)};
                locs.pb({y + 1, x + 1});
            } else {
                lb[y][x][0] = lb[y - 1][x][0];
                lb[y][x][1] = lb[y][x - 1][1];
            }
            // cout << "{" << lb[y][x][0] << " " << lb[y][x][1] << "} ";
        }
        // cout << "\n";
    }

    adj.assign(sz(locs) * 2 + 2, vector<array<int,3>>(0));
    int src = sz(locs) * 2, snk = src + 1;;
    function<void(int,int,int)> addedge = [&](int u, int v, int cap) {
        int c1 = sz(caps);
        caps.pb(cap);
        int c2 = sz(caps);
        caps.pb(0);
        adj[u].pb({v, c1, c2});
        adj[v].pb({u, c2, c1});
    };
    for(int i = 0; i < sz(locs); i++) {
        addedge(src, i, 1);
        addedge(sz(locs) + i, snk, 1);
    }
    for(int y = 0; y < n; y++) {
        for(int x = 0; x < m; x++) {
            if(A[y][x] == 0) {
                addedge(lb[y][x][0], sz(locs) + lb[y][x][1], 1);
            }
        }
    }

    dinic(src, snk);

    //debug(sz(locs));
    //for(int i = 0; i < sz(locs); i++) {
    //    for(auto& e : adj[i]) if(e[0] < src) {
    //        debug(i, e[0], caps[e[1]], caps[e[2]]);
    //    }
    //}

    visx.assign(sz(locs), 0);
    visy.assign(sz(locs), 0);
    for(int i = 0; i < sz(locs); i++) {
        bool matched = 0;
        for(auto& e : adj[i]) {
            if(e[0] < sz(locs) * 2 && caps[e[2]] == 1) {
                matched = 1;
            }
        }
        // debug(matched);
        if(!matched) {
            bilabel(i);
        }
    }
    //for(int i = 0; i < sz(locs); i++) {
    //    cout << visy[i] << " ";
    //}
    //cout << "\n";
    //for(int i = 0; i < sz(locs); i++) {
    //    cout << visx[i] << " ";
    //}
    //cout << "\n";

    int cnt = 0;
    for(int i = 0; i < sz(locs); i++) {
        if(!visy[i]) {
            cnt++;
        }
        if(visx[i]) {
            cnt++;
        }
    }

    cout << cnt << "\n";
    for(int i = 0; i < sz(locs); i++) {
        if(!visy[i]) {
            cout << locs[i][0] << " " << locs[i][1] << " DOLJE\n";
        }
        if(visx[i]) {
            cout << locs[i][0] << " " << locs[i][1] << " DESNO\n";
        }
    }
}
