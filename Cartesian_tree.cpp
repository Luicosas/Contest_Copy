#include<iostream>
#include<vector>
#include<functional>

using namespace std;

int main(){
    int n; cin >> n;

    vector<int> vals(n);
    for(int& i : vals) cin >> i;

    vector<int> parent(n); parent[0] = 0;
    vector<pair<int,int>> child(n, {INT_MAX, INT_MAX});
    int root = 0;
    for(int i = 1; i < n; i++){
        parent[i] = i - 1;
        while(vals[parent[i]] > vals[i] && parent[i] != parent[parent[i]]) parent[i] = parent[parent[i]];
        if(parent[i] == parent[parent[i]] && vals[parent[i]] > vals[i]){
            child[i].first = parent[i];
            parent[parent[i]] = i;
            parent[i] = i;
            root = i;
        } else {
            if(child[parent[i]].second != INT_MAX){
                child[i].first = child[parent[i]].second;
                parent[child[i].first] = i;
            }
            child[parent[i]].second = i;
        }
    }

    function<void(int)> inorder = [&](int idx){
        if(child[idx].first != INT_MAX) inorder(child[idx].first);
        cout << vals[idx] << " ";
        if(child[idx].second != INT_MAX) inorder(child[idx].second);
    }; inorder(root);

    cout << "\n";
    for(int i = 0; i < n; i++) cout << parent[i] + 1 << " ";
}
