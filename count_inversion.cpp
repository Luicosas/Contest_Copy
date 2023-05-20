// the binary index tree only works on number > 0 
// time complexity of O(nlnln) space complexity of O(ln)
int count_inversions(vector<int>& arr){
    int size = -INT_MAX;
    for(int& i : arr) size = max(size, i);

    int ans = 0; map<int,int> BIT;
    for(int i = (int)arr.size() - 1; i >= 0; i--){
        for(int idx = arr[i] - 1; idx != 0; idx ^= (idx & -idx)) 
            ans += BIT[idx];
        for(int idx = arr[i]; idx <= size; idx += (idx & -idx))
            BIT[idx]++;
    }

    return ans;
}
