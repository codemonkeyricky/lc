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
    vector<int> getFactors(int n)
    {
        vector<int> factors;
        for (int f = 2; f * f <= n; ++f)
            while (n % f == 0)
                factors.push_back(f), n /= f;
        if (n > 1)
            factors.push_back(n);
        return factors;
    }

public:
    int minOperations(vector<int> &nums, vector<int> &div)
    {
        sort(begin(nums), end(nums));
        sort(begin(div), end(div));

        if (nums[0] == 1)
            return 0;

        vector<int> factors = getFactors(div[0]);
        vector<int> common;
        for (auto &d : div)
        {
            for (auto &f : factors)
                if (d % f == 0)
                    common.push_back(f), d /= f;
            if (common.empty())
                return -1;
            swap(common, factors);
            common.clear(); 
        }

        int rv = 0;
        auto part = factors;
        for (auto &n : nums)
        {
            auto all = getFactors(n);
            int i, j;
            for (i = j = 0; j < all.size(); ++j, ++i)
            {
                while (i < part.size() && part[i] != all[j])
                    ++i;
                if (i >= part.size())
                    break;
            }
            if (j >= all.size())
                return rv;
            ++rv;
        }
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minOperations(vector<int>() = {44, 7, 10, 8, 19, 15, 44, 35, 25, 29, 40, 41, 26, 1, 48, 29, 26, 7, 10, 50, 40, 4, 34, 20, 46, 9, 23, 26, 28, 47, 15, 46, 2, 49, 44, 1, 7, 24, 2, 13, 39, 3, 40, 20, 42, 3, 43, 7, 26, 1, 6, 15, 43, 33, 28, 14, 35, 11}, vector<int>() = {17, 28, 13, 17, 33, 10, 27, 17, 16});
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {37, 37}, vector<int>() = {399309920, 289361645});
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {40, 38, 18, 19, 18, 18, 16}, vector<int>() = {430222122, 345833946, 609158196, 173124594, 25468560, 990277596, 295095510, 354571344, 931500936, 636837210});
    cout << r << endl;

    r = sol.minOperations(vector<int>() = {2, 3, 2, 4, 3}, vector<int>() = {9, 6, 9, 3, 15});
    cout << r << endl;
}