#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include<stdint.h>
#include<stack>
#include<map>
#include<queue>
#include<functional>

#define MAX64 0x7fffffffffffffff 
#define MAX32 0x7fffffff
#define ll int_fast64_t
#define int int_fast32_t

using namespace std;

struct graph{
    struct edge{ int to, weight; };
    vector<vector<edge>> nodes;

    graph(int size) : nodes(size){}

    void one_way_connect(int from, int to, int weight){
        nodes[from].push_back({to, weight});
    }

    ll dijkstra(int from, int to){
        struct update{ll idx, dis;};
        auto compare = [](update& a, update& b){ return a.dis > b.dis; };
        priority_queue<update, vector<update>, bool(*)(update&,update&)> qu(compare);
        qu.push({from, 0});

        vector<ll> min_dis(nodes.size(), MAX64);
        
        while(!qu.empty()){
            update crnt = qu.top();
            qu.pop();
            
            if(crnt.dis > min_dis[crnt.idx]) continue;
            
            min_dis[crnt.idx] = crnt.dis;
            if(crnt.idx == to) break;

            for(edge& e : nodes[crnt.idx]){
                if(crnt.dis + e.weight >= min_dis[e.to]) continue;
                qu.push({e.to, crnt.dis + e.weight});
            }
        }

        return min_dis[to];
    }

    vector<vector<ll>> floyd_warshall(){
        vector<vector<ll>> min_dis(nodes.size(), vector<ll>(nodes.size(), MAX64));

        for(int i = 0; i < nodes.size(); i++){
            min_dis[i][i] = 0;
        }

        for(int i = 0; i < nodes.size(); i++){
            for(edge& e : nodes[i]){
                min_dis[i][e.to] = e.weight;
            }
        }

        for(int k = 0; k < nodes.size(); k++){
            for(int i = 0; i < nodes.size(); i++){
                for(int j = 0; j < nodes.size(); j++){
                    if(min_dis[i][k] == MAX64 || min_dis[k][j] == MAX64) continue;
                    min_dis[i][j] = min(min_dis[i][j], min_dis[i][k] + min_dis[k][j]);
                }
            }
        }

        return min_dis;
    }
};
