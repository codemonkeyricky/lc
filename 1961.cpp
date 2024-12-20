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
    bool isPrefixString(string s, vector<string> &words)
    {
        int i = 0;
        for (int j = 0; j < words.size() && i < s.size(); ++j)
            for (auto ch : words[j])
                if (i == s.size() || s[i++] != ch)
                    return false;
        return i == s.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isPrefixString("iloveleetcode", vector<string>() = {"i", "love", "leetcode", "apples"});
    cout << r << endl;
}