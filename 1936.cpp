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
    int addRungs(vector<int> &rungs, int dist)
    {
        int rv = 0, h = 0;
        for (auto &r : rungs)
        {
            if (h + dist < r)
            {
                int h1 = r - h;
                int k = h1 / dist;
                rv += h1 / dist;
                if (h + k * dist >= r)
                    --rv;
            }
            h = r; 
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.addRungs(vector<int>() = {3}, 1);
    cout << r << endl;

    r = sol.addRungs(vector<int>() = {1, 3, 5, 10}, 2);
    cout << r << endl;
}