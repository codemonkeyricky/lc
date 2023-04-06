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

class Solution
{
public:
    double maxPrice(vector<vector<int>> &items, int capacity)
    {
        sort(begin(items), end(items), [](vector<int> &l, vector<int> &r)
             { return (double)l[0] / l[1] >= (double)r[0] / r[1]; });
            
        double rv = 0;
        int k = 0;
        while (k < items.size() && capacity)
        {
            int p = items[k][0]; 
            int w = items[k][1];
            if (capacity >= w)
                rv += p, capacity -= w;
            else if (capacity < w)
                rv += (double)capacity / w * p, capacity = 0;
            ++k;
        }
        return !capacity ? rv : -1;
    }
};

int main()
{
    Solution sol;
    double r;

    r = sol.maxPrice(vector<vector<int>>() = {{50, 1}, {10, 8}}, 5);
    cout << r << endl;
}