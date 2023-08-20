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
    int dfs(string &s, set<int> &powers, int k, int mask)
    {
        if (k >= s.size())
            return powers.count(mask) ? 1 : 1e9;

        int a = 1e9, b = 1e9;
        if (powers.count(mask) && (s[k] - '0'))
            a = 1 + dfs(s, powers, k + 1, (s[k] - '0'));
        b = dfs(s, powers, k + 1, (mask << 1) | (s[k] - '0'));
        return min(a, b);
    }

public:
    int minimumBeautifulSubstrings(string s)
    {
        if (s[0] == '0')
            return -1;

        set<int> powers;
        for (auto i = 1; i < (1 << 16); i *= 5)
            powers.insert(i);
        int rv = dfs(s, powers, 0, 0);
        return rv >= 1e9 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumBeautifulSubstrings("00001111001111");
    cout << r << endl;

    r = sol.minimumBeautifulSubstrings("101101111101");
    cout << r << endl;

    r = sol.minimumBeautifulSubstrings("1011");
    cout << r << endl;
}