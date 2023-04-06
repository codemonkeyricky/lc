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
    bool validPartition(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n + 1);
        dp[0] = 1;

        for (auto i = 1; i < n; ++i)
        {
            bool a, b, c;
            a = b = c = false;
            if (i >= 1)
                a = nums[i] == nums[i - 1];
            if (i >= 2)
                b = nums[i] == nums[i - 1] && nums[i - 1] == nums[i - 2];
            if (i >= 2)
                c = nums[i] == nums[i - 1] + 1 && nums[i - 1] == nums[i - 2] + 1;

            auto k = i + 1;
            if (a && dp[k - 2])
                dp[k] = true;
            else if (i >= 2 && b && dp[k - 3])
                dp[k] = true;
            else if (i >= 2 && c && dp[k - 3])
                dp[k] = true;
        }
        return dp[n];
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}