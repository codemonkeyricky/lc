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
    int maxSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        priority_queue<array<int, 2>> q;
        for (auto i = 0; i < n; ++i)
            q.push({-nums[i], i});

        vector<array<int, 32>> bits(n + 2);
        for (auto i = 0; i <= n; ++i)
        {
            bits[i + 1] = bits[i];
            for (auto k = 0; i < n && k < 32; ++k)
                if (nums[i] & (1 << k))
                    ++bits[i + 1][k];
        }

        int sum = -1;
        int rv = 0;
        set<int> index = {0, n + 1};
        while (q.size())
        {
            auto [v, k] = q.top();
            q.pop();

            auto sub = nums[k];
            auto r = index.lower_bound(k);
            auto l = prev(r);

            for (auto b = 0; b < 32; ++b)
                if (bits[k + 1][b] - bits[*l][b] == 0)
                    sub &= ~(1 << b);

            for (auto b = 0; b < 32; ++b)
                if (bits[*r][b] - bits[k + 1][b] == 0)
                    sub &= ~(1 << b);

            index.insert(k + 1);

            if (sum == -1)
                sum = sub;
            else if (sum != sub)
                return rv;

            ++rv;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxSubarrays(vector<int>() = {5, 7, 1, 3});
    cout << r << endl;

    r = sol.maxSubarrays(vector<int>() = {1, 0, 2, 0, 1, 2});
    cout << r << endl;
}