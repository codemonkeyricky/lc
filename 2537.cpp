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
    long long countGood(vector<int> &nums, int k)
    {
        long long pairs = 0, rv = 0, n = nums.size(), i, j;
        map<int, int> count;
        for (i = 0, j = 0; j < n; ++j)
        {
            if (++count[nums[j]] > 1)
                pairs += count[nums[j]] - 1;

            while (i < n && pairs >= k)
            {
                rv += n - j;
                pairs -= --count[nums[i++]];
            }
        }

        while (i < n && pairs >= k)
        {
            ++rv;
            pairs -= --count[nums[i++]];
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countGood(vector<int>() = {2, 3, 1, 3, 2, 3, 3, 3, 1, 1, 3, 2, 2, 2}, 18);
    cout << r << endl;

    r = sol.countGood(vector<int>() = {3, 1, 4, 3, 2, 2, 4}, 2);
    cout << r << endl;

    r = sol.countGood(vector<int>() = {1, 1, 1, 1, 1}, 10);
    cout << r << endl;
}