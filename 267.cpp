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
    void dfs(array<int, 26> &chars, string &curr, int odd, unordered_set<string> &rv)
    {
        array<int, 26> empty = {};
        if (chars == empty)
        {
            auto rev = curr;
            reverse(begin(rev), end(rev));
            rv.insert(curr + (odd != -1 ? string(1, odd + 'a') : "") + rev);
        }

        for (auto i = 0; i < 26; ++i)
            if (chars[i])
            {
                curr += i + 'a';
                chars[i] -= 2;
                dfs(chars, curr, odd, rv);
                chars[i] += 2;
                curr.pop_back();
            }
    }
public:
    vector<string> generatePalindromes(string s)
    {
        array<int, 26> chars = {};
        for (auto &c : s)
            ++chars[c - 'a'];

        int odd = -1;
        for (auto i = 0; i < 26; ++i)
            if (chars[i] % 2)
                if (odd == -1)
                    odd = i;
                else
                    return {};

        if (odd != -1)
            --chars[odd];
        unordered_set<string> rv;
        string curr;
        dfs(chars, curr, odd, rv);
        return {begin(rv), end(rv)};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.generatePalindromes("abc");
    sol.generatePalindromes("aabb");
}