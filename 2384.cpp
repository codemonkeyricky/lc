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
    string largestPalindromic(string num)
    {
        vector<int> dig(10);
        for (auto &n : num)
            ++dig[n - '0'];
        
        string rv; 
        for (int i = 9; i >= 0; --i)
            if (i != 0 || rv.size())
                rv += string(dig[i] / 2, i + '0'), dig[i] -= dig[i] / 2 * 2;

        string m;
        for (int i = 9; i >= 0 && m.empty(); --i)
            if (dig[i])
                m = string(1, i + '0');

        string rrv(rbegin(rv), rend(rv));

        return rv + m + rrv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}