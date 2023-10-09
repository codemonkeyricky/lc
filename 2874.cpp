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
    long long maximumTripletValue(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> r(n);

        int mmax = 0;
        for (int i = n - 1; i >= 0; --i)
            r[i] = mmax = max(nums[i], mmax);

        long long rv = 0;
        long long big = nums[0], small = 1e9;
        for (auto i = 1; i < n - 1; ++i)
        {
            small = (long long)nums[i];
            rv = max(rv, (big - small) * r[i + 1]);
            big = max(big, (long long)nums[i]);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumTripletValue(vector<int>() = {8, 6, 3, 13, 2, 12, 19, 5, 19, 6, 10, 11, 9});
    cout << r << endl;

    r = sol.maximumTripletValue(vector<int>() = {1, 10, 3, 4, 19});
    cout << r << endl;

    r = sol.maximumTripletValue(vector<int>() = {12, 6, 1, 2, 7});
    cout << r << endl;
}