//#pragma GCC optimize("O3","unroll-loops")
//#pragma GCC target("avx","avx2")
#include<bits/stdc++.h>
 
#ifdef LOCAL
#include<debug.h>
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

using namespace std;

#define ll int64_t
#define sz(x) (int)(x).size()

struct fenwick_tree{
    int maxn; map<int, int> vals;
    fenwick_tree(int N) : maxn(N) {}
    int qry(int l, int r){
        int ans = 0;
        for(int i = r; i; i ^= (i & -i))
            ans += vals[i];
        for(int i = l - 1; i; i ^= (i & -i))
            ans -= vals[i];
        return ans;
    }
    void add(int idx, int val){
        for(ll i = idx; i <= maxn; i += (i & -1)) {
            vals[(int)i] += val;
        }
    }
};
