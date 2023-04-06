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
    int minimizeArrayValue(vector<int> &nums)
    {
        long l = 1, r = 1e9;
        int n = nums.size();
        vector<long> nums2;
        for (auto &n : nums)
            nums2.push_back(n);

        while (l < r)
        {
            auto copy = nums2;
            long m = (l + r) / 2;
            for (int i = n - 1; i >= 1; --i)
                if (nums2[i] > m)
                {
                    auto d = nums2[i] - m;
                    nums2[i] -= d;
                    nums2[i - 1] += d;
                }

            if (nums2[0] <= m)
                r = m;
            else
                l = m + 1;

            swap(copy, nums2);
        }
        return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimizeArrayValue(vector<int>() = {2, 7, 9, 19, 5, 19});
    cout << r << endl;

    r = sol.minimizeArrayValue(vector<int>() = {3, 7, 1, 6});
    cout << r << endl;
}