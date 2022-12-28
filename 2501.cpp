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
    int longestSquareStreak(vector<int> &nums)
    {
        unordered_set<long> set(begin(nums), end(nums));
        unordered_set<long> seen;
        sort(begin(nums), end(nums));
        int rv = -1;
        for (auto n : nums)
        {
            int streak = 0;
            while (!seen.count(n) && set.count(n))
            {
                ++streak;
                seen.insert(n);
                n = n * n;
            }
            rv = max(rv, streak);
        }
        return rv >= 2 ? rv : -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestSquareStreak(vector<int>() = {4, 3, 6, 16, 8, 2});
    cout << r << endl;
}