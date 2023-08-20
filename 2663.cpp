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
    bool dfs(string &s, int k, int kk, bool same, string &rv)
    {
        int n = s.size();
        if (k >= n)
            return s != rv;

        for (auto j = same ? s[k] - 'a' : 0; j < kk; ++j)
        {
            rv[k] = j + 'a';

            if (k > 0 && rv[k] == rv[k - 1])
                continue;

            if (k > 1 && rv[k] == rv[k - 2])
                continue;

            if (dfs(s, k + 1, kk, same && s[k] == rv[k], rv))
                return true;
        }
        return false;
    }

public:
    string smallestBeautifulString(string s, int k)
    {
        int n = s.size();
        string rv(n, '#');
        if (dfs(s, 0, k, true, rv))
            return rv;
        return "";
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.smallestBeautifulString("dc", 4);
    cout << r << endl;

    r = sol.smallestBeautifulString("abcz", 26);
    cout << r << endl;
}