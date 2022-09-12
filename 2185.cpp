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
    int prefixCount(vector<string> &words, string pref)
    {
        long long rhash = 0, p = 1, mod = 1e9 + 7;
        for (auto &c : pref)
            rhash *= 26, rhash = (rhash + c - '0') % mod;

        int rv = 0;
        for (long long i = 0, hash = 0; i < words.size(); ++i, rv += rhash == hash, hash = 0)
            for(auto j = 0; j < words[i].size() && j < pref.size(); ++j)
                hash *= 26, hash = (hash + words[i][j] - '0') % mod;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.prefixCount(vector<string>() = {"pay", "attention", "practice", "attend"}, "at");
    cout << r << endl;
}