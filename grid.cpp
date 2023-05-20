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

using namespace std;

struct grid{
    vector<vector<int>> vals;

    const vector<pair<int,int>> sharing_edge_neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const vector<pair<int,int>> eight_by_eight_neighbors = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    
    grid(int size_x, int size_y) : vals(size_x, vector<int>(size_y, 0)) {}

    void read_in(){
        for(int y = 0; y < vals[0].size(); y++){
            for(int x = 0; x < vals.size(); x++){
                cin >> vals[x][y];
            }
        }
    }

    bool in_bound(int x, int y){
        return (x >= 0 && x < vals.size() && y >= 0 && y < vals[x].size());
    }

    int get_neightboring_tiles_sum(int x, int y, vector<pair<int,int>> neightbors){
        int ans = 0;
        for(pair<int,int>& loc : neightbors){
            if(!in_bound(x + loc.first, y + loc.second)) continue;
            ans += vals[x + loc.first][y + loc.second];
        }
        return ans;
    }
};