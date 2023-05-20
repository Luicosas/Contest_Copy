#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<stdint.h>

using namespace std;

struct sum_seg_tree{
    vector<int> tree;
    int size;
    
    sum_seg_tree(int n, vector<int> init = {}) : size(n){
        tree.resize(n * 2 - 1);
        for(int& i : tree) i = 0;
        for(int i = 0; i < n && i < init.size(); i++){
            tree[i + n - 1] = init[i];
        }

        for(int i = n-2; i >= 0; i--){
            calc(i);
        }
    }

    int get_sum(int l, int r){
        int tree_size = (tree.size() + 1) / 2;
        l += tree_size - 1;
        r += tree_size - 1;

        int ans = 0;
        while(l < r){
            if(l % 2 == 0){
                ans += tree[l];
                l++;
            }
            if(r % 2 == 1){
                ans += tree[r];
                r--;
            }
            l = (l - 1) / 2;
            r = (r - 1) / 2;
        }
        if(l == r){
            ans += tree[l];
        }

        return ans;
    }

    void update(int idx, int val){
        idx += (tree.size() + 1) / 2 - 1;
        tree[idx] = val;
        while(idx > 0){
            calc((idx - 1) / 2);
            idx = (idx - 1) / 2;
        }
        return;
    }

private:
    void calc(int idx){
        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }
};