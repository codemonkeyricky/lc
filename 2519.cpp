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
    static constexpr int N = 100001;

    vector<int> bit;
    int get(int k)
    {
        int rv = 0;
        for (++k; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

    void update(int k)
    {
        for (++k; k < N; k += k & -k)
            ++bit[k];
    }

public:
    int kBigIndices(vector<int> &nums, int k)
    {
        vector<int> dp(nums.size(), 1e9);

        bit = vector<int>(N);
        for (auto i = 0; i < nums.size(); ++i)
        {
            dp[i] = min(dp[i], get(nums[i] - 1));
            update(nums[i]);
        }

        bit = vector<int>(N);
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            dp[i] = min(dp[i], get(nums[i] - 1));
            update(nums[i]);
        }

        return count_if(begin(dp), end(dp), [k](const int n)
                        { return n >= k; });
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.kBigIndices(vector<int>() = {2, 3, 6, 5, 2, 3}, 2);
    cout << r << endl;
}