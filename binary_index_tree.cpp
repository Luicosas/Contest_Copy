struct binary_index_tree{
    int size;
    
    vector<int> arr;
    binary_index_tree(int _size) : size(_size), arr(_size)  { }

    //map<int,int> arr;
    //binary_index_tree(int _size) : size(_size) {  }

    int qry(int _l, int _r){
        int ans = 0;
        for(int i = _l; i != 0; i ^= (i & -i)) ans -= arr[i - 1];
        for(int i = _r + 1; i != 0; i ^= (i & -i)) ans += arr[i - 1];
        return ans;
    }

    void add(int _idx, int _val){
        for(int i = _idx + 1; i <= size; i += (i & -i)) arr[i - 1] += _val;
    }
};
