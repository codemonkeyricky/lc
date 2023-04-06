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
    int maxCount(vector<int> &banned, int n, long long maxSum)
    {
        long long l = 0, r = n;
        sort(begin(banned), end(banned));
        while (l < r)
        {
            auto m = (l + r + 1) / 2;
            auto sum = (m * (m + 1)) / 2;
            for (auto k = 0; k < banned.size() && banned[k] <= m; ++k)
                sum -= banned[k];

            if (sum <= maxSum)
                l = m; 
            else
                r = m - 1;
        }

        int chosen = l;
        for (auto k = 0; k < banned.size() && banned[k] <= l; ++k)
            --chosen;

        return chosen; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxCount(vector<int>() = {4, 3, 5, 6}, 7, 18);
    cout << r << endl;

    r = sol.maxCount(vector<int>() = {1, 4, 6}, 6, 4);
    cout << r << endl;
}