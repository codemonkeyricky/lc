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
    int longestPalindrome(string s)
    {
        array<int, 26> chars = {}, CHARS = {};
        for (auto &c : s)
            if ('a' <= c && c <= 'z')
                ++chars[c - 'a'];
            else if ('A' <= c && c <= 'Z')
                ++CHARS[c - 'A'];

        int rv = 0, odd = 0;
        for (auto i = 0; i < 26; ++i)
            rv += chars[i] / 2 * 2, odd += chars[i] % 2;

        for (auto i = 0; i < 26; ++i)
            rv += CHARS[i] / 2 * 2, odd += CHARS[i] % 2;

        return rv + (odd ? 1 : 0);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestPalindrome("abccccdd");
    cout << r << endl;
}