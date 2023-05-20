#include <iostream>

#include <set>

using namespace std;

set <int> nums;
int ans[5900];

string suffix(int x){
    if(x%100 >= 11 && x%100 <= 13) return "th";
    if(x%10 == 1) return "st";
    else if(x%10 == 2) return "nd";
    else if(x%10 == 3) return "rd";
    else return "th";
}

void construct(){
    nums.insert(1);
    int i = 1;
    for(auto it = nums.begin(); it != nums.end() && i < 5850; i++, it++){
        ans[i] = *it;
        nums.insert(*it * 2);
        nums.insert(*it * 3);
        nums.insert(*it * 5);
        nums.insert(*it * 7);
    }
}


int main () {
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL);
    construct();
    int in;
    for(int i = 0; i < 10; i++) cout << ans[i] << " ";
    while(cin >> in && in){
        cout << "The " << in << suffix(in) << " humble number is " << ans[in] << ".\n";
    }
}
