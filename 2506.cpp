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
    int similarPairs(vector<string> &words)
    {
        map<int, int> count;
        for (auto &word : words)
        {
            int a = 0;
            for (auto &c : word)
                a |= 1 << (c - 'a');
            ++count[a];
        }

        int rv = 0;
        for (auto &c : count)
            rv += (c.second * (c.second - 1)) / 2;
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.similarPairs(vector<string>() = {"aabb", "ab", "ba"});
    cout << r << endl;

    r = sol.similarPairs(vector<string>() = {"aba", "aabb", "abcd", "bac", "aabc"});
    cout << r << endl;
}