ll pow_while_loop(ll base, ll exponent){
    ll ans = 1;
    while(exponent > 0){
        if((exponent & 1) == 1) ans *= base;
        base *= base;
        exponent >>= 1;
    }
    return ans;
}
