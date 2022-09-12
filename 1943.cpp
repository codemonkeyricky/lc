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
    vector<vector<long long>> splitPainting(vector<vector<int>> &segments)
    {
        vector<int> dp(100001);
        for (auto &segment : segments)
        {
            auto i = segment[0], j = segment[1], k = segment[2];
            dp[i] += k;
            dp[j] -= k;
        }

        vector<vector<long long>> rv;
        long long sum = 0;
        for (auto i = 0, j = 0; j < dp.size(); ++j)
        {
            if (dp[j])
            {
                if (sum)
                    rv.push_back({i, j, sum});
                i = j;
            }

            sum += dp[j];
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.splitPainting(vector<vector<int>>() = {{1, 4, 5}, {4, 7, 7}, {1, 7, 9}});
    cout << r << endl;
}