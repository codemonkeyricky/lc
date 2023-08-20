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
    void dfs(int k, int mask, vector<vector<pair<int, char>>> &children, vector<int> &masks)
    {
        masks[k] = mask;
        ++cnt[mask];
        for (auto &[u, c] : children[k])
            dfs(u, mask ^ (1 << (c - 'a')), children, masks);
    }

    unordered_map<int, int> cnt;

public:
    long long countPalindromePaths(vector<int> &parent, string s)
    {
        cnt.clear();
        int n = parent.size();
        vector<vector<pair<int, char>>> children(n);
        for (auto i = 1; i < n; ++i)
            children[parent[i]].push_back({i, s[i]});
        vector<int> masks(n);
        dfs(0, 0, children, masks);

        long long rv = 0;
        for(auto i = 1; i < n; ++i)
        {
            for (auto k = 0; k < 26; ++k)
                rv += cnt[masks[i] ^ (1 << k)];
            --cnt[masks[i]];
            rv += cnt[masks[i]];
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPalindromePaths(vector<int>() = {-1, 0, 0, 0, 0}, "aaaaa");
    cout << r << endl;

    r = sol.countPalindromePaths(vector<int>() = {-1, 0, 0, 1, 1, 2}, "acaabc");
    cout << r << endl;
}