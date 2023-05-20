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

int main (){
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); 
    std::cout << std::fixed << std::setprecision(10);

    string S; cin >> S; S += '$';

    vector<int> suffix(sz(S)), label(sz(S)); 
    for(int i = 0; i < sz(S); i++) {
        suffix[i] = i;
        label[i] = S[i];
    }
    for(int len = 1; len <= sz(S); len *= 2){
        sort(suffix.begin(), suffix.end(), [&](int& a, int& b){
            if(label[a] != label[b]) return label[a] < label[b];
            else return label[(a + len) % sz(label)] < label[(b + len) % sz(label)];
        });
        vector<int> tmp(sz(S), 0); 
        for(int i = 1, id = 0; i < sz(label); i++){
            id += label[suffix[i - 1]] != label[suffix[i]];
            id += label[(suffix[i - 1] + len) % sz(label)] != label[(suffix[i] + len) % sz(label)];
            id -= (id > tmp[suffix[i - 1]] + 1);
            tmp[suffix[i]] = id; 
        }
        swap(tmp, label);
    }

    /* int Q; cin >> Q;
    while(Q--){
        string substring; cin >> substring;
        auto low = lower_bound(suffix.begin(), suffix.end(), substring, [&](int a, const string& sub){
            for(int i = 0; i + a < sz(S) && i < sz(sub); i++){
                if(S[i + a] < sub[i]) return true;
                if(S[i + a] > sub[i]) return false;
            }
            return false;
        });
        auto upp = upper_bound(suffix.begin(), suffix.end(), substring, [&](const string& sub, int a){
            for(int i = 0; i + a < sz(S) && i < sz(sub); i++){
                if(sub[i] < S[i + a]) return true;
                if(sub[i] > S[i + a]) return false;
            }
            return false;
        });
        cout << upp - low << "\n";
    } */

    /* vector<int> lcp(sz(S) - 1, 0); 
    for(int i = 0, k = 0; i < sz(S); i++){
        if(label[i] - 1 < 0) continue;
        while(S[i + k] == S[suffix[label[i] - 1] + k]) k++;
        lcp[label[i] - 1] = k;
        k = max(k - 1, 0);
    } */

    return 0;
}
