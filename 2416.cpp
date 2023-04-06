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
    struct Trie
    {
        array<Trie *, 26> map = {};
    };

    Trie root;

public:
    vector<int> sumPrefixScores(vector<string> &words)
    {
        unordered_map<Trie *, int> dp;
        auto trie = &root;
        for (int i = 0; i < words.size(); ++i, trie = &root)
        {
            for (auto j = 0; j < words[i].size(); ++j)
            {
                if (!trie->map[words[i][j] - 'a'])
                    trie->map[words[i][j] - 'a'] = new Trie();
                trie = trie->map[words[i][j] - 'a'];
                ++dp[trie];
            }
        }

        vector<int> rv;
        for (int i = 0, r = 0; i < words.size(); ++i, rv.push_back(r), r = 0, trie = &root)
        {
            for (auto j = 0; j < words[i].size(); ++j)
            {
                trie = trie->map[words[i][j] - 'a'];
                r += dp[trie];
            }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.sumPrefixScores(vector<string>() = {"abc", "ab", "bc", "b"});
    cout << r << endl;
}