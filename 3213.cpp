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

    int dfs(string &target, int k, Trie *n)
    {
        if (k >= target.size())
            return (n == &root) ? 0 : n->cost;
            
        int index = target[k] - 'a';

        if (dp[k].count(n))
            return dp[k][n];

        int rv = 1e9;

        if (n->lookup[index])
        {
            // current letter matchs

            auto nn = n->lookup[index];

            int a = 1e9, b = 1e9;

            // if this can be a word, start a new word
            // if (nn->cost != 1e9)
            a = nn->cost + dfs(target, k + 1, &root);

            // try matching the next word
            b = dfs(target, k + 1, nn);

            rv = min(a, b);
        }
        return dp[k][n] = rv;
    }

    vector<map<Trie *, int>> dp;

public:
    int minimumCost(string target, vector<string> &words, vector<int> &costs)
    {
        dp = vector<map<Trie *, int>>(target.size());

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

        int rv = dfs(target, 0, &root);
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