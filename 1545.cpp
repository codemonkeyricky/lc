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
    string inv(string s)
    {
        string rv;
        for (auto &c : s)
            rv.push_back(c == '1' ? '0' : '1');
        return rv;
    }

    string rev(string s)
    {
        return string(rbegin(s), rend(s));
    }

    string dfs(int n)
    {
        if (!n)
            return "0";
        string s = dfs(n-1);
        return s + "1" + rev(inv(s));
    }
public:
    char findKthBit(int n, int k)
    {
        auto r = dfs(n - 1);
        return r[k];
    }
};


int main()
{
    Solution sol;
    char r;

    r = sol.findKthBit(2, 0);
    cout << r << endl;

    r = sol.findKthBit(3, 0);
    cout << r << endl;


    r = sol.findKthBit(4, 11);
    cout << r << endl;
}