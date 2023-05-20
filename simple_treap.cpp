//problem : https://codeforces.com/gym/102787/my
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

#define pb push_back
#define ll int64_t
#define sz(x) (int)(x).size()
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct t_node {
    int val, pri, size;
    t_node *c[2];
    t_node(int v) {
        val = v;
        pri = (int)rng();
        size = 1;
        c[0] = c[1] = nullptr;
    }
    ~t_node() {
        if(c[0]) {
            delete c[0];
        }
        if(c[1]) {
            delete c[1];
        }
    }
};

void update(t_node* t) {
    t->size = 1;
    if(t->c[0]) {
        t->size += t->c[0]->size;
    }
    if(t->c[1]) {
        t->size += t->c[1]->size;
    }
}

array<t_node*,2> split(t_node* t, int v, int add = 0) {
    if(!t) {
        return {t, t};
    }

    int t_val = add + (t->c[0] ? t->c[0]->size : 0);
    if(t_val >= v) {
        auto p = split(t->c[0], v, add);
        t->c[0] = p[1];
        update(t);
        return {p[0], t};
    } else {
        auto p = split(t->c[1], v, t_val + 1);
        t->c[1] = p[0];
        update(t);
        return {t, p[1]};
    }
}

t_node* merge(t_node* l, t_node* r) {
    if(!l || !r) {
        return (l ? l : r);
    }

    assert((ll)r > 0);
    assert((ll)l > 0);
    if(l->pri > r->pri) {
        l->c[1] = merge(l->c[1], r);
        update(l);
        return l;
    } else {
        r->c[0] = merge(l, r->c[0]);
        update(r);
        return r;
    }
}
template<typename... T> 
t_node* merge(t_node* h, T... t) {
    return merge(h, t...);
}

ostream& operator <<(ostream& os, t_node* t) {
    if(!t) {
        return os;
    }
    os << t->c[0];
    os << t->val << " ";
    os << t->c[1];
    return os;
}

int main (){
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); 
    std::cout << std::fixed << std::setprecision(10);

    int n;
    cin >> n;

    t_node* root = nullptr;
    for(int i = 1; i <= n; i++) {
        root = merge(root, new t_node(i));
    }

    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if(a >= b) {
            continue;
        }
        int len = min(b - a, n - b + 1);

        t_node* t[5]; array<t_node*, 2> p;
        p = split(root, b + len - 1);
        t[4] = p[1];
        p = split(p[0], b - 1);
        t[3] = p[1];
        p = split(p[0], a + len - 1);
        t[2] = p[1];
        p = split(p[0], a - 1);
        t[1] = p[1];
        t[0] = p[0];

        root = merge(t[0], merge(t[3], merge(t[2], merge(t[1], t[4]))));
    }

    cout << root << "\n";
    delete root;    

    return 0;
}

