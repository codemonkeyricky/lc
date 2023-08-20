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
    int minOperations(vector<int> &nums)
    {
        int n = nums.size();

        auto ones = count_if(begin(nums), end(nums), [](int i)
                             { return i == 1; });
        if (ones)
            return n - ones;

        int rv = 1e9;
        for (auto i = 0; i < n - 1; ++i)
        {
            auto g = nums[i];
            for (auto j = i + 1; j < n; ++j)
            {
                g = gcd(g, nums[j]);
                if (g == 1)
                {
                    rv = min(rv, n + j - i - 1);
                    break;
                }
            }
        }

        return rv == 1e9 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {2, 6, 3, 4});
    cout << r << endl;
}