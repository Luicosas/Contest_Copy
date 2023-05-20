#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, a) for(int i = 0; i < a; i++)

struct Node {
    int sum, l, r;
    Node *lc, *rc;

    Node(int bL, int bR){
        l = bL, r = bR, sum = 0;
        if(bL == bR){
            lc = rc = nullptr;
        } else {
            int m = (bL + bR) / 2;
            lc = new Node(bL, m);
            rc = new Node(m + 1, bR);
        }
    }

    ~Node(){
        delete lc;
        delete rc;
    }

    void add(int x, int v){
        sum += v;
        if(l == r) return;
        if(x >= (l + r) / 2) rc->add(x,v);
        else lc->add(x,v);
    }

    int qry(int qL, int qR){
        //cout << "q" << qL << " " << qR << " " << l << " " << r << endl;
        if(qL > r || qR < l) return 0;
        if(qL <= l && qR >= r) return sum;
        return lc->qry(qL, qR) + rc->qry(qL, qR);
    }
};
