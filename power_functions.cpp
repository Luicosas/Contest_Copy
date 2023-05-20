#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<stdint.h>

typedef int_fast64_t ll;
typedef int_fast64_t i64;
typedef int_fast32_t i32;

ll pow_recursion(ll base, ll exponent){
    if(exponent == 0) return 1;
    ll ans = pow_recursion(base, exponent / 2);
    ans *= ans;
    if(exponent % 2 == 1) ans *= base;
    return ans;
}

ll pow_recursion_with_modulo(ll base, ll exponent, ll MOD){
    if(exponent == 0) return 1;
    ll h = pow_recursion_with_modulo(base, exponent/2, MOD);
    h = h * h % MOD;
    if((exponent & 1) == 0) return h;
    else return h * base % MOD;
}

ll pow_while_loop(ll base, ll exponent){
    ll ans = 1;
    while(exponent > 0){
        if((exponent & 1) == 1) ans *= base;
        base *= base;
        exponent >>= 1;
    }
    return ans;
}

ll pow_while_loop_with_modulo(ll base, ll exponent, ll MOD){
    ll ans = 1;
    while(exponent > 0){
        if((exponent & 1) == 1) ans = ans * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return ans;
}

i32 choose(i32 out_of, i32 choose, i32 mod){
    i32 ans = 1;
    for(i32 i = 0; i < choose; i++) ans = ans * (out_of - i) % mod;
    for(i32 i = choose; i > 0; i--) ans = ans / i % mod;
    return ans;
}
