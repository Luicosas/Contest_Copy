#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define sz(x) (int)(x.size())
#define itr(x) x.begin(), x.end()
#define prv(x) for(auto& i : x) cout << i << " "; cout << "\n";
#define debug(...) cerr << #__VA_ARGS__ << " : "; for(auto& i : {__VA_ARGS__}) cerr << i << " "; cerr << "\n";

int mod = 998244353, pr = 3; 

int mul(int a, int b) {
    return ((ll)a * b) % mod;
}

int add(int a, int b) {
    a += b;
    a -= (a >= mod) * mod;
    return a;
}

int fpow(int b, int e) {
    int ret = 1;
    while(e > 0) {
        if(e & 1) {
            ret = mul(ret, b);
        }
        b = mul(b, b);
        e >>= 1;
    }
    return ret;
}

int inv(int v) {
    return fpow(v, mod - 2);
}

// recursive function
// length of poly must be a power of 2
vector<int> fft(vector<int> poly) {
    int n = sz(poly);

    if(n == 1) {
        return poly;
    }

    vector<int> e(n / 2, 0), o(n / 2, 0);
    for(int i = 0; i < n / 2; i++) {
        e[i] = poly[i * 2];
        o[i] = poly[i * 2 + 1];
    }
    
    vector<int> ep = fft(e), op = fft(o); 

    int rn = fpow(pr, (mod - 1) / n), r2 = fpow(pr, (mod - 1) / 2);
    vector<int> ret(n, 0);
    for(int i = 0, rni = 1, rnin = fpow(pr, (mod - 1) / 2); i < n / 2; i++) {
        ret[i] = add(ep[i], mul(rni, op[i]));
        ret[i + n / 2] = add(ep[i], mul(rnin, op[i]));
        rni = mul(rn, rni);
        rnin = mul(rn, rnin);
    }
    return ret;
}

// faster non-recursive function
vector<int> fft(const vector<int>& poly, int n) {
    vector<int> dp(n, 0), sdp(n);
    for(int i = 0; i < n; i++) {
        int loc = 0;
        for(int f = n / 2, t = 1; t < n; f /= 2, t *= 2) {
            loc |= t * ((i & f) > 0);
        }
        if(loc < sz(poly)) {
            dp[i] = poly[loc];
        }
    }

    for(int len = 2; len <= n; len *= 2) {
        int r2 = fpow(3, (mod - 1) / 2), rl = fpow(3, (mod - 1) / len);
        for(int st = 0; st < n; st += len) {
            int rli = 1, rlib = r2;
            for(int i = 0; i < len / 2; i++) {
                sdp[st + i] = add(dp[st + i], mul(rli, dp[st + len / 2 + i]));
                sdp[st + + len / 2 + i] = add(dp[st + i], mul(rlib, dp[st + len / 2 + i]));
                rli = mul(rl, rli);
                rlib = mul(rl, rlib);
            }
        }
        swap(dp, sdp);
    }
    return dp;
}

vector<int> ifft(vector<int> ftv) {
    vector<int> ret = fft(ftv, sz(ftv));
    reverse(ret.begin() + 1, ret.end());
    int div = inv(sz(ret));
    for(int& i : ret) {
        i = mul(i, div);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n = 2;

    vector<int> A{1, 1, 0, 0}, B{3, 0, 0, 0};
    vector<int> Ap = fft(A, 4), Bp = fft(B, 4);
    
    vector<int> Cp(sz(Ap));
    for(int i = 0; i < sz(A); i++) {
        Cp[i] = mul(Ap[i], Bp[i]);
    }

    vector<int> C = ifft(Cp);
}
