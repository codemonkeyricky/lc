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
    int smallestFactorization(int n)
    {
        if(n == 1)
            return 1;

        map<int, int> f;
        for (auto i = 2; i < 10; ++i)
            while (n % i == 0)
                ++f[i], n /= i;

        if (n >= 10)
            return 0;

        vector<int> nums;
        for (auto &ff : f)
        {
            switch (ff.first)
            {
            case 2:
                while (ff.second >= 3)
                {
                    nums.push_back(8);
                    ff.second -= 3;
                }
                break;
            case 3:
                while (ff.second >= 2)
                {
                    nums.push_back(9);
                    ff.second -= 2;
                }
                break;
            case 5:
            case 7:
            {
                while (ff.second)
                {
                    nums.push_back(ff.first);
                    --ff.second;
                }
            }
            }
        }

        if (f[2] && f[3])
            nums.push_back(6), --f[2], --f[3];
        if (f[2] == 2)
            nums.push_back(4), f[2] -= 2;
        if (f[2] == 1)
            nums.push_back(2), --f[2];
        if (f[3])
            nums.push_back(3), --f[3];

        sort(begin(nums), end(nums));
        long rv = 0;
        for (auto &s : nums)
            rv = rv * 10 + s;

        return rv >= INT_MAX ? 0 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.smallestFactorization(4);
    cout << r << endl;

    // r = sol.smallestFactorization(3000000);
    // cout << r << endl;

    // r = sol.smallestFactorization(22);
    // cout << r << endl;

    // r = sol.smallestFactorization(11);
    // cout << r << endl;

    r = sol.smallestFactorization(15);
    cout << r << endl;

    r = sol.smallestFactorization(48);
    cout << r << endl;
}