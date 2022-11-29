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
    int countGoodStrings(int low, int high, int zero, int one)
    {
        vector<long> dp(high + 1);
        dp[0] = 1;
        for (auto i = 1; i < high + 1; ++i)
            dp[i] = ((i - zero >= 0 ? dp[i - zero] : 0) + (i - one >= 0 ? dp[i - one] : 0)) % 1000000007;

        int rv = 0;
        for(auto i = low; i <= high; ++i)
            rv = (rv + dp[i]) % 1000000007;
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countGoodStrings(200, 200, 10, 1);
    cout << r << endl;

    r = sol.countGoodStrings(3, 3, 1, 1);
    cout << r << endl;
}