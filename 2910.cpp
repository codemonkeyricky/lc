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
        unordered_map<int, int> m;
        for (auto &n : nums)
            ++m[n];

        map<int, int> cnt;
        for (auto &mm : m)
            ++cnt[mm.second];

        int rv = 1e9;
        auto limit = cnt.begin()->first;
        for (auto x = 1; x <= limit; ++x)
        {
            bool valid = true;
            int g = 0;
            for (auto &c : cnt)
            {
                int f = c.first;
                int a = f / (x + 1);
                int b = f % (x + 1);
                if (b == 0)
                    g += a * c.second;
                else if (x - b <= a)
                    g += (a + 1) * c.second;
                else
                    valid = false;
                if (!valid)
                    break;
            }

            if (valid)
                rv = min(rv, g);
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minGroupsForValidAssignment(vector<int>() = {1, 2, 2, 3, 1});
    cout << r << endl;

    r = sol.minGroupsForValidAssignment(vector<int>() = {1, 2, 3, 3, 3, 3, 3});
    cout << r << endl;

    r = sol.minGroupsForValidAssignment(vector<int>() = {10, 10, 10, 3, 1, 1});
    cout << r << endl;

    r = sol.minGroupsForValidAssignment(vector<int>() = {3, 2, 3, 2, 3});
    cout << r << endl;
}