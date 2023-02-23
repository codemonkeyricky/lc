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
    int squareFreeSubsets(vector<int> &nums)
    {
        // Find all factors <= 30
        unordered_map<int, int> lookup;
        for (auto i = 2; i < 31; ++i)
            for (int k = 2, ii = i; k <= i; ++k)
                while (ii % k == 0)
                    lookup[i] |= 1 << k, ii /= k;

        lookup[4] = lookup[8] = lookup[9] = lookup[12] =
            lookup[16] = lookup[18] = lookup[20] = lookup[24] =
                lookup[25] = lookup[27] = lookup[28] = 0;

        unordered_map<long , long> cnt;
        long rv = 0;
        for (auto &n : nums)
        {
            if (n == 1 || lookup[n])
            {
                auto copy_cnt = cnt;
                for (auto &c : copy_cnt)
                    if (n == 1 || !(lookup[n] & lookup[c.first]))
                    {
                        rv = (rv + c.second) % 1000000007;
                        cnt[n * c.first] = (cnt[n * c.first] + c.second) % 1000000007;
                        lookup[n * c.first] = lookup[n] | lookup[c.first];
                    }
                ++cnt[n];
                ++rv;
            }
        }

        return rv;
    }
};


int main()
{
    Solution sol;
    int r;

    r = sol.squareFreeSubsets(vector<int>() = {1, 1, 1});
    cout << r << endl;

    r = sol.squareFreeSubsets(vector<int>() = {3, 5, 6, 7, 9, 10, 11, 13});
    cout << r << endl;

    r = sol.squareFreeSubsets(vector<int>() = {1, 1, 1});
    cout << r << endl;

    r = sol.squareFreeSubsets(vector<int>() = {26, 6, 4, 27, 6, 18});
    cout << r << endl;

    // r = sol.squareFreeSubsets(vector<int>() = {11, 2, 19, 7, 9, 27});
    // cout << r << endl;

    r = sol.squareFreeSubsets(vector<int>() = {3, 4, 4, 5});
    cout << r << endl;
}