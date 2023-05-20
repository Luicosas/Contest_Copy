#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<stdint.h>

struct disjoint_set{
    std::vector<int> parents;
    std::vector<int> sizes;

    disjoint_set(int size):
        parents(size), sizes(size,1)
    {
        for(int i = 0; i < size; i++) parents[i] = i;
    }

    int get_root(int idx){
        if(parents[idx] != idx) parents[idx] = get_root(parents[idx]);
        return parents[idx];
    }

    void join(int a, int b){
        a = get_root(a); b = get_root(b);
        if(a == b) return;

        if(sizes[a] > sizes[b]) std::swap(a,b);
        parents[a] = b;
        sizes[b] += sizes[a]; 
    }
};