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
    int dfs(vector<int> &cookies, vector<int> &curr, int k)
    {
        if (k >= cookies.size())
            return *max_element(begin(curr), end(curr));
        
        int rv = 1e9;
        for (auto i = 0; i < curr.size(); ++i)
        {
            curr[i] += cookies[k];
            rv = min(rv, dfs(cookies, curr, k + 1));
            curr[i] -= cookies[k];
        }
        return rv;
    }
public:
    int distributeCookies(vector<int> &cookies, int k)
    {
        vector<int> dp(k);
        return dfs(cookies, dp, 0);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}