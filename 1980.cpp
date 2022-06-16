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
    string findDifferentBinaryString(vector<string> &nums)
    {
        int l = nums[0].size();
        vector<bool> dp(1 << l);
        for (auto &s : nums)
        {
            int n = 0;
            for (auto &c : s)
                n <<= 1, n += c - '0';
            dp[n] = 1;
        }

        string rv(l, '0');
        for (auto i = 0; i < dp.size(); ++i)
            if (!dp[i])
            {
                for (auto j = 0; j < l && i; ++j, i >>= 1)
                    rv[j] += (i & 1);
                reverse(begin(rv), end(rv));
                return rv;
            }

        return "";
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}