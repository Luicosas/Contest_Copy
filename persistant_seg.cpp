#include<bits/stdc++.h>
#include<functional>
using namespace std;

#define ll long long
#define rep(i, a, b) for(int i = a; i < b; i++)
#define pb push_back
#define pii pair<int,int>

struct Node {
    int l, r;
    Node *lc, *rc;
    int sum;

    Node(int lb, int rb){
        l = lb; r = rb; sum = 0;

        if(lb == rb) lc = rc = nullptr;
        else {
            int mid = (l + r) / 2;
            lc = new Node(lb, mid);
            rc = new Node(mid+1, rb);
        }
    }

    int qry(int qL, int qR){
        if(qL > qR || qL > r || qR < l) return 0;
        if(qL <= l && r <= qR) return sum;
        return lc->qry(qL, qR) + rc-> qry(qL,qR);
    }

    Node* add(int idx, int val){
        Node *nw = new Node(*this);
        nw->sum += val;
 
        if(l == r) return nw;

        if(idx <= (l + r) / 2) nw->lc = lc->add(idx, val);
        else nw->rc = rc->add(idx, val);
        
        return nw;
    }
};

int main(){
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); 
    std::cout << std::fixed << std::setprecision(10);

    int n, q;
    cin >> n >> q;

    vector<Node*> roots(1, new Node(0, n)); 
    for(int i = 0; i < n; i++){
        int buf; cin >> buf;
        roots.push_back(roots.back()->add(buf - 1, 1));
        //cout << roots.back()->sum << "\n";
    }

    while(q--){
        int l, r, a, b;
        cin >> l >> r >> a >> b;
        a--; b--;
        //cout << roots[r]->qry(a, b) << " " <<  roots[l - 1]->qry(a, b);
        cout << roots[r]->qry(a, b) - roots[l - 1]->qry(a, b) << "\n";
    }
}
