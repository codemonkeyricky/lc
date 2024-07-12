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
    int maxSubarrayLength(vector<int> &nums, int k)
    {
        map<int, int> cnt;
        int n = nums.size(), rv = 0;
        for (auto i = 0, j = 0; j < n; ++j)
        {
            if (++cnt[nums[j]] <= k)
                rv = max(rv, j - i + 1);
            else
                while (--cnt[nums[i++]] != k)
                    ;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxSubarrayLength(vector<int>() = {1, 4, 4, 3}, 1);
    cout << r << endl;

    r = sol.maxSubarrayLength(vector<int>() = {1, 2, 1, 2, 1, 2, 1, 2}, 1);
    cout << r << endl;

    r = sol.maxSubarrayLength(vector<int>() = {1, 2, 3, 1, 2, 3, 1, 2}, 2);
    cout << r << endl;
}