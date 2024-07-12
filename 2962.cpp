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
    long long countSubarrays(vector<int> &nums, int k)
    {
        int mmax = *max_element(begin(nums), end(nums));

        long long rv = 0;
        long long n = nums.size(), kk = 0;
        for (long long li = 0, i = 0, j = 0; j < n; ++j)
        {
            if (nums[j] == mmax)
                ++kk;

            if (kk == k)
            {
                while (kk == k)
                    kk -= nums[i++] == mmax;

                rv = rv + (i - li) * (n - j);

                li = i;
            }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countSubarrays(vector<int>() = {1, 4, 2, 1}, 3);
    cout << r << endl;

    r = sol.countSubarrays(vector<int>() = {1, 3, 2, 3, 3}, 2);
    cout << r << endl;
}