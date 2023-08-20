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
    long long maxStrength(vector<int> &nums)
    {
        sort(begin(nums), end(nums));

        vector<int> neg;
        long long rv = -1e9;

        bool zero = false;
        for (auto &n : nums)
            if (n < 0)
                neg.push_back(n);
            else if(n == 0)
                zero = true;
            else
            {
                if (rv == -1e9)
                    rv = 1;
                rv *= n;
            }

        sort(begin(neg), end(neg));

        if (neg.size() >= 2)
        {
            if (rv == -1e9)
                rv = 1;

            for (auto i = 0; i < neg.size() / 2 * 2; ++i)
                rv *= neg[i];
        }

        return rv != -1e9 ? rv : zero ? 0
                                      : nums[0];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxStrength(vector<int>() = {3, -1, -5, 2, 5, -9});
    cout << r << endl;
}