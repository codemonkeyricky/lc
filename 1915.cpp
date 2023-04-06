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
    long long wonderfulSubstrings(string word)
    {
        unordered_map<int, int> dp;
        dp[0] = 1;
        int mask = 0;
        long long rv = 0;
        for (auto &c : word)
        {
            mask ^= 1 << (c - 'a');
            rv += dp[mask];
            for (auto i = 0; i < 10; ++i)
                rv += dp[mask ^ (1 << i)];
            ++dp[mask];
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.wonderfulSubstrings("aabb");
    cout << r << endl;
}