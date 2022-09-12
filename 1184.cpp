#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

class Solution {
public:
    int distanceBetweenBusStops(vector<int>& d, int src, int dst) {
        
        auto sum = accumulate(begin(d),end(d), 0); 
        
        auto dist = 0;
        while (src != dst)
        {
            dist += d[src];
            src = (src + 1) % d;
        }
        
        return min(dist, sum - dist); 
    }
};



int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}