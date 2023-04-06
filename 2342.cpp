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
    int maximumSum(vector<int> &nums)
    {
        unordered_map<int, array<int, 2>> dp;
        for (auto &n : nums)
        {
            int sum = 0;
            int copy = n;
            while (n)
                sum += n % 10, n /= 10;
            n = copy;
            if (n > dp[sum][0])
                swap(dp[sum][0], dp[sum][1]), dp[sum][0] = n;
            else if (n > dp[sum][1])
                dp[sum][1] = n;
        }

        int rv = 0;
        for (auto &d : dp)
            if (d.second[0] && d.second[1])
                rv = max(rv, d.second[0] + d.second[1]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumSum(vector<int>() = {18, 43, 36, 13, 7});
    cout << r << endl;
}