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
    bool makeStringsEqual(string s, string target)
    {
        array<int, 2> cnt1 = {}, cnt2 = {}, rv = {};
        for (auto &c : s)
            ++cnt1[c - '0'];
        for (auto &c : target)
            ++cnt2[c - '0'];

        int mzero = min(cnt1[0], cnt2[0]);
        int mone = min(cnt1[1], cnt2[1]);

        if (cnt1[1] == 0 && cnt2[1] == 0)
            return true;

        return cnt1[1] > 0 && cnt2[1] > 0;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.makeStringsEqual("101110100", "110011000");
    cout << r << endl;

    r = sol.makeStringsEqual("11", "00");
    cout << r << endl;
}