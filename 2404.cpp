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
    int mostFrequentEven(vector<int> &nums)
    {
        map<int, int> dp;
        for (auto i = 0; i < nums.size(); ++i)
            if (!(nums[i] & 1))
                ++dp[nums[i]];

        int count = -1, rv = -1;
        for (auto i = 0; i < nums.size(); ++i)
            if (!(nums[i] & 1))
                if (dp[nums[i]] > count || (dp[nums[i]] == count && nums[i] < rv))
                    count = dp[nums[i]], rv = nums[i];

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.mostFrequentEven(vector<int>() = {0, 1, 2, 2, 4, 4, 1});
    cout << r << endl;
}