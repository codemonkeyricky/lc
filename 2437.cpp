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
    int countTime(string time)
    {
        int rv = 0;
        for (auto i = 0; i < 24; ++i)
            for (auto j = 0; j < 60; ++j)
            {
                string h = "00", m = "00";
                h[0] += i / 10, h[1] += i % 10;
                m[0] += j / 10, m[1] += j % 10;
                auto s = h + ":" + m;
                int match = true;
                for (auto k = 0; k < 5 && match; ++k)
                    if (time[k] != '?' && time[k] != s[k])
                        match = false;
                rv += match;
            }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countTime("?5:00");
    cout << r << endl;
}