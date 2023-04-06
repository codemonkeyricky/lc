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
    bool matchReplacement(string s, string sub, vector<vector<char>> &mappings)
    {
        unordered_map<char, unordered_set<char>> remap;
        for (auto &m : mappings)
            remap[m[0]].insert(m[1]);

        vector<unordered_set<char>> possible(sub.size());
        for (auto i = 0; i < sub.size(); ++i)
        {
            possible[i].insert(sub[i]);
            possible[i].insert(begin(remap[sub[i]]), end(remap[sub[i]]));
        }

        vector<int> kmp(possible.size());
        for (auto j = 0, i = 1; i < possible.size(); ++i)
        {
            bool match = false;
            for (auto &c : possible[i])
                if (possible[j].find(c) != possible[j].end())
                {
                    match = true;
                    break;
                }

            if (match)
                kmp[i] = ++j;
            else if (j)
            {
                j = kmp[j - 1];
                --i;
            }
        }

        // kmp
        int i = 0, j = 0, n = s.size();
        while (i < n)
        {
            if (possible[j].count(s[i]))
                ++i, ++j;

            if (j == possible.size())
                return true;
            else if (i < n && !possible[j].count(s[i]))
            {
                if (j)
                    j = kmp[j - 1];
                else
                    ++i;
            }
        }
        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.matchReplacement("fool3e7bar", "leet", vector<vector<char>>() = {{'e', '3'}, {'t', '7'}, {'t', '8'}});
    cout << r << endl;
}