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
    int findTheLongestBalancedSubstring(string s)
    {
        int n = s.size(), zeroes = 0, ones = 0, rv = 0;
        if (s[0] == '1')
            ++ones;
        else
            ++zeroes;

        for (auto i = 1; i < n; ++i)
        {
            if (s[i - 1] == '0' && s[i] == '0')
                ++zeroes;
            else if (s[i-1] == '0' && s[i] == '1')
                ++ones;
            else if (s[i - 1] == '1' && s[i] == '0')
                ones = 0, zeroes = 1;
            else if (s[i - 1] == '1' && s[i] == '1')
                ++ones;
            rv = max(rv, min(ones, zeroes) * 2);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findTheLongestBalancedSubstring("01011");
    cout << r << endl;
}