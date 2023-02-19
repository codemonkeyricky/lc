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
    using vvi = vector<vector<int>>;
    using vi = vector<int>;

public:
    int maxValue(vector<vector<int>> &events, int kk)
    {
        vector<array<int, 3>> evts = {{0, 0, 0}};
        for (auto &e : events)
            evts.push_back({e[1], e[0], e[2]});
        sort(begin(evts), end(evts));

        int n = evts.size();
        vvi dp(n, vi(kk));
        for (auto i = 0; i < n; ++i)
        {
            if (i)
                dp[i] = dp[i - 1];
            for (auto k = 0; k < kk; ++k)
            {
                array<int, 3> look = {evts[i][1], 0, 0};
                auto it = prev(upper_bound(begin(evts), end(evts), look));
                dp[i][k] = max(evts[i][2] + (k ? dp[it - begin(evts)][k - 1] : 0), dp[i][k]);
            }
        }

        int rv = 0;
        for (auto i = 0; i < n; ++i)
            for (auto k = 0; k < kk; ++k)
                rv = max(rv, dp[i][k]);

        return rv;
    }
};

using vvi = vector<vector<int>>;
using vi = vector<int>;

int main()
{
    Solution sol;
    int r;

    r = sol.maxValue(vvi() = {{19, 42, 7}, {41, 73, 15}, {52, 73, 84}, {84, 92, 96}, {6, 64, 50}, {12, 56, 27}, {22, 74, 44}, {38, 85, 61}}, 5);
    cout << r << endl;

    r = sol.maxValue(vvi() = {{1, 2, 4}, {3, 4, 3}, {2, 3, 10}}, 2);
    cout << r << endl;

    r = sol.maxValue(vvi() = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}}, 3);
    cout << r << endl;
}