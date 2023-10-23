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
    int minGroupsForValidAssignment(vector<int> &nums)
    {
        // int last = -1;
        // for (auto &n : nums)
        //     if (last == -1)
        //         last = n;
        //     else 

        int n = nums.size();
        int l = 1, r = nums.size();
        int rv = 1e9;
        while (l < r)
        {
            int m = (l + r + 1) / 2;

            int mmin = 1e9, mmax = 0;
            unordered_map<int, int> cnt;
            for (auto &n : nums)
                if (++cnt[n] > m + 1)
                    cnt[n] = 1, mmax = m + 1;

            bool valid = true;
            for (auto &c : cnt)
                mmin = min(mmin, c.second), mmax = max(mmax, c.second);

            if (mmax - mmin <= 1)
                l = m;
            else
                r = m - 1;
        }

        unordered_map<int, int> cnt;
        int groups = 0;
        for (auto &n : nums)
            if (++cnt[n] > l + 1)
                cnt[n] = 1, ++groups;

        return cnt.size() + groups;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minGroupsForValidAssignment(vector<int>() = {1, 1, 1, 1, 1});
    cout << r << endl;

    r = sol.minGroupsForValidAssignment(vector<int>() = {1, 2, 3, 3, 3, 3, 3});
    cout << r << endl;

    r = sol.minGroupsForValidAssignment(vector<int>() = {10, 10, 10, 3, 1, 1});
    cout << r << endl;

    r = sol.minGroupsForValidAssignment(vector<int>() = {3, 2, 3, 2, 3});
    cout << r << endl;
}