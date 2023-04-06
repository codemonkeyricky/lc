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
    vector<vector<int>> indexPairs(string text, vector<string> &words)
    {
        int MOD = 1000000007;
        vector<vector<int>> rv;
        for (auto &w : words)
        {
            long hash = 0;
            long power = 1; 
            for (auto &c : w)
            {
                hash = (hash * 26 + c - 'a') % MOD;
                power = (power * 26) % MOD;
            }

            long rolling = 0;
            for (auto i = 0; i <= text.size(); ++i)
            {
                if (i >= w.size() && rolling == hash)
                    rv.push_back({i - (int)w.size(), i - 1});

                if (i < text.size())
                    rolling = (rolling * 26 + text[i] - 'a') % MOD;

                if (i >= w.size())
                {
                    rolling -= (text[i-w.size()] - 'a') * power;
                    while (rolling < 0)
                        rolling += MOD;
                }
            }
        }

        sort(begin(rv), end(rv));

        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    sol.indexPairs("thestoryofleetcodeandme", vector<string>() = {"story", "fleet", "leetcode"});
    sol.indexPairs("ababa", vector<string>() = {"aba", "ab"});
}