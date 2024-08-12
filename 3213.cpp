#include <iostream>
#include <array> 
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
    struct Trie {
        array<Trie *, 26> lookup = {};
        int cost = 1e9;
    };

    Trie root;

    void match(string &target, int k, int l, Trie *n, vector<pair<int, int>> &result)
    {
        int index = target[k] - 'a';

        if (n->cost != 1e9)
            result.push_back({l, n->cost});

        if (k >= target.size())
            return;

        if (n->lookup[index])
            match(target, k + 1, l + 1, n->lookup[index], result);
    }

    int dfs(string &target, int k)
    {
        if (k >= target.size())
            return 0;

        if (dp[k])
            return dp[k];

        vector<pair<int, int>> result;
        match(target, k, 0, &root, result);

        int rv = 1e9;
        for (auto &[len, cost] : result)
        {
            int temp = cost + dfs(target, k + len);
            rv = min(temp, rv);
        }

        return dp[k] = rv;
    }

    vector<int> dp;

public:
    int minimumCost(string target, vector<string> &words, vector<int> &costs)
    {
        dp = vector<int>(target.size());

        for (auto k = 0; k < words.size(); ++k)
        {
            auto word = words[k];
            auto r = &root;
            for (auto &kk : word)
            {
                auto c = kk - 'a';
                if (!r->lookup[c])
                    r->lookup[c] = new Trie();
                r = r->lookup[c];
            }
            r->cost = min(r->cost, costs[k]);
        }

        int rv = dfs(target, 0);
        return rv >= 1e9 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumCost(string("mmnj"), vector<string>() = {"nj", "m", "mn", "mmnj"}, vector<int>() = {2, 4, 3, 3});
    cout << r << endl;

    r = sol.minimumCost(string("kkphlc"), vector<string>() = {"hl", "c", "kkp"}, vector<int>() = {6, 10, 17});
    cout << r << endl;

    r = sol.minimumCost(string("mooaiwrb"), vector<string>() = {"o", "m", "wrb", "o", "ai"}, vector<int>() = {2, 1, 2, 1, 1});
    cout << r << endl;

    r = sol.minimumCost(string("aaaa"), vector<string>() = {"z", "zz", "zzz"}, vector<int>() = {1, 10, 100});
    cout << r << endl;

    r = sol.minimumCost(string("abcdef"), vector<string>() = {"abdef", "abc", "d", "def", "ef"}, vector<int>() = {100, 1, 1, 10, 5});
    cout << r << endl;
}