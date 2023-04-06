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
    int reductionOperations(vector<int> &nums)
    {
        map<int, int> dp;
        for (auto &n : nums)
            ++dp[n];
        int rv = 0, r = 0;
        for (auto it = dp.rbegin(); it != prev(dp.rend()); ++it)
            r += it->second, rv += r;
        return rv;
    }
};

class Solution
{
public:
    vector<int> xorQueries(vector<int> &arr, vector<vector<int>> &queries)
    {
        int n = arr.size(); 
        vector<int> dp(n); 
        int r = 0;
        for (auto i = 0; i < n; ++i)
            r ^= arr[i], dp[i] = r;
        vector<int> rv;
        for (auto &q : queries)
        {
            auto i = q[0], j = q[1];
            rv.push_back(dp[j] ^ (i ? dp[i - 1] : 0));
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.reductionOperations(vector<int>() = {7, 9, 10, 8, 6, 4, 1, 5, 2, 3});
    cout << r << endl;
}