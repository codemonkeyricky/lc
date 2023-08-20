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
    bool checkArray(vector<int> &nums, int k)
    {
        int n = nums.size(), add = 0, i = 0, delta = 0; 
        vector<int> dp(n + 1);
        for (auto i = 0; i <= n - k; ++i)
        {
            add += dp[i];
            delta = -(nums[i] + add);
            add += delta;
            dp[i + k] = -delta;
        }

        for (auto i = n - k + 1; i < n; ++i)
        {
            add += dp[i];
            if (nums[i] + add != 0)
                return false;
        }
        
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.checkArray(vector<int>() = {60, 72, 87, 89, 63, 52, 64, 62, 31, 37, 57, 83, 98, 94, 92, 77, 94, 91, 87, 100, 91, 91, 50, 26}, 4);
    cout << r << endl;

    r = sol.checkArray(vector<int>() = {2, 2, 3, 1, 1, 0}, 3);
    cout << r << endl;

    r = sol.checkArray(vector<int>() = {2, 2, 3, 1, 1, 0}, 3);
    cout << r << endl;
}