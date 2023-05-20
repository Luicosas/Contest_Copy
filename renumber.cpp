void renumber(vector<int>& nums){
    vector<pair<int,int>> re(nums.size());
    for(int i = 0; i < nums.size(); i++) re[i] = {nums[i], i};
    sort(re.begin(), re.end());
    int id = 0, prev = re[0].first;
    for(int i = 0; i < nums.size(); i++){
        if(prev != re[i].first) id++;
        prev = re[i].first;
        nums[re[i].second] = id;
    }
}
