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
    int dfs(int n, int i, int j, int k, string &s)
    {
        if (i < 0 || i >= n || j < 0 || j >= n)
            return -1;
        
        if(k >= s.size())
            return 0;
        
        switch(s[k])
        {
        case 'R': return 1 + dfs(n, i, j + 1, k + 1, s);
        case 'D': return 1 + dfs(n, i + 1, j, k + 1, s);
        case 'L': return 1 + dfs(n, i, j - 1, k + 1, s);
        case 'U': return 1 + dfs(n, i- 1, j, k + 1, s);
        default:
            return -1e9;
        }
    }

public:
    vector<int> executeInstructions(int n, vector<int> &startPos, string s)
    {
        vector<int> rv;
        for (auto i = 0; i < s.size(); ++i)
            rv.push_back(dfs(n, startPos[0], startPos[1], i, s));
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.executeInstructions(3, vector<int>() = {0, 1}, "RRDDLU");
}