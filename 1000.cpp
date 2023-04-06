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
    int mergeStones(vector<int> &stones, int k)
    {
        int n = stones.size();
        vector<int> cumul(n);

        auto sum = [=](int i, int j) -> int
        {
            return cumul[j] - (i ? cumul[i - 1] : 0);
        };

        for (auto i = 0; i < n; ++i)
            cumul[i] = (i ? cumul[i - 1] : 0) + stones[i];

        vector<vector<int>> dp(n, vector<int>(n));

        // base
        for (auto i = 0; i + k < n; ++i)
            dp[i][i + k] = sum(i, i + k);

        for (auto kk = k * 2 - 1; kk < n; ++k)
        {
            int rv = 1e9; 
            for (auto i = 0; i + kk < n; ++i)
            {
                rv = min(rv, sum(i,kk) - sum)
            }
        }
            

    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}