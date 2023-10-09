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
    long long maximumSumOfHeights(vector<int> &h)
    {
        int n = h.size();

        vector<array<long long, 2>> l, r; ///< index, sum
        vector<long long> lsum(n), rsum(n);
        for (long long i = 0; i < n; ++i)
        {
            while (l.size() && h[l.back()[0]] > h[i])
                l.pop_back();

            if (l.size())
                l.push_back({i,
                             l.back()[1] + (i - l.back()[0]) * h[i]});
            else
                l.push_back({i, (i + 1) * h[i]});

            lsum[i] = l.back()[1];
        }

        for (long long i = n - 1; i >= 0; --i)
        {
            while (r.size() && h[r.back()[0]] > h[i])
                r.pop_back();

            if (r.size())
                r.push_back({i,
                             r.back()[1] + (r.back()[0] - i) * h[i]});
            else
                r.push_back({i, (n - i) * h[i]});

            rsum[i] = r.back()[1];
        }

        long long rv = rsum[0];
        for (auto i = 0; i < n - 1; ++i)
            rv = max(rv, lsum[i] + rsum[i + 1]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumSumOfHeights(vector<int>() = {5, 3, 4, 1, 1});
    cout << r << endl;
}