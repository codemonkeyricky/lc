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
    int garbageCollection(vector<string> &garbage, vector<int> &travel)
    {
        int i, g, p, m, rv;
        for (rv = i = g = p = m = 0; i < garbage.size(); ++i)
        {
            for (auto &c : garbage[i])
                if (c == 'G')
                    g = max(g, i);
                else if (c == 'P')
                    p = max(p, i);
                else if (c == 'M')
                    m = max(m, i);
            rv += garbage[i].size();
        }

        for (auto i = 0; i < travel.size(); ++i)
        {
            if (i < g)
                rv += travel[i];
            if (i < m)
                rv += travel[i];
            if (i < p)
                rv += travel[i];
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.garbageCollection(vector<string>() = {"G", "P", "GP", "GG"}, vector<int>() = {2, 4, 3});
    cout << r << endl;
}