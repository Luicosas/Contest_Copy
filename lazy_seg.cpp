#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, a) for(int i = 0; i < a; i++)

struct Node {
    int l, r;
    Node *lc, *rc;
    int sum;

    Node(int qL, int qR){
        l = qL; r = qR;
        if(qL == qR - 1){
            sum = 0;
            lc = rc = nullptr;
        } else {
            int qM = (qL + qR) / 2;
            lc = new Node(qL, qM);
            rc = new Node(qM, qR);
            sum = 0;
        }
    }

    void add(int x, int v){
        if(l == r - 1) sum += v;
        else {
            int m = (l + r) / 2;
            if(x < m) lc->add(x, v);
            else rc->add(x,v);
            sum = lc->sum + rc->sum;
        }
    }

    int qry(int qL, int qR){
        if(r <= qL || l >= qR) return 0;
        if(qL <= l && r >= qR) return sum;
        int m = (l + r) / 2;
        return lc->qry(qL, qR) + rc->qry(qL, qR);
    }

    ~Node(){
        delete lc;
        delete rc;
    }
};

int main (){
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); 
    std::cout << std::fixed << std::setprecision(10);
    
    Node* seg = new Node(1, 5);
    seg->add(2,2);
    seg->add(3,-1);
    cout << seg->qry(3,5) << "\n";    

    delete seg;
    
    return 0;
}
