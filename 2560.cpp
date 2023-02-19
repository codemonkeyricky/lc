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
    int minCapability(vector<int> &nums, int k)
    {
        int l = 1, r = 1e9;
        while (l < r)
        {
            auto m = (l + r) / 2;
            vector<int> index, dp; 
            for (auto i = 0; i < nums.size(); ++i)
                if (nums[i] <= m)
                    index.push_back(i);

            if (index.size() >= k)
            {
                dp = vector<int>(index.size());
                dp[0] = 1;
                for (auto i = 1; i < index.size(); ++i)
                {
                    dp[i] = 1 + (i >= 2 ? dp[i - 2] : 0);
                    if (index[i - 1] + 1 < index[i])
                        dp[i] = max(dp[i], 1 + dp[i - 1]);
                }
            }

            if (index.size() >= k && max(dp[index.size() - 1], index.size() >= 2 ? dp[index.size() - 2] : -1) >= k)
                r = m;
            else 
                l = m + 1;
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minCapability(vector<int>() = {1, 4, 5}, 1);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {24, 109, 117, 142, 98, 94, 91, 130, 73, 48, 107, 77}, 5);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {24, 1, 55, 46, 4, 61, 21, 52}, 3);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {35, 9, 18, 78, 40, 8, 71, 2, 59}, 5);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {9, 6, 20, 21, 8}, 3);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {4, 22, 11, 14, 25}, 3);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {2, 7, 9, 3, 1}, 2);
    cout << r << endl;

    r = sol.minCapability(vector<int>() = {2, 3, 5, 9}, 2);
    cout << r << endl;
}