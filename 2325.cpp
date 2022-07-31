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
    string decodeMessage(string key, string message)
    {
        vector<int> map(26, -1);
        for (auto i = 0, j = 0; i < key.size(); ++i)
            if (key[i] != ' ' && map[key[i] - 'a'] == -1)
                map[key[i] - 'a'] = j++;

        string rv;
        for (auto &c : message)
            if (c != ' ')
                rv += map[c - 'a'] + 'a';
            else
                rv += " ";
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.decodeMessage("the quick brown fox jumps over the lazy dog", "vkbs bs t suepuv");
    cout << r << endl;
}