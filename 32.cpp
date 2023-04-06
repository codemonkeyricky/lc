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
    int longestValidParentheses(string s)
    {
        vector<pair<char, int>> stack; ///< value / index pair
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            if (s[i] == ')' && stack.size() && stack.back().first == '(')
            {
                int t = stack.back().second;
                s[t] = '*';
                s[i] = '*';
                stack.pop_back();
            }
            else
                stack.push_back({s[i], i});
        }

        int rv = 0, cnt = 0, i = 0; 
        while(i < n)
            if (s[i] == '*')
                rv = max(rv, ++cnt);
            else 
                cnt = 0;

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.longestValidParentheses(")()())");
    cout << r << endl;
}