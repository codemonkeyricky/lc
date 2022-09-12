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
    unordered_set<string> visited;
    string rv;
    int a, b, n;

    string rotate(string s, int x)
    {
        reverse(s.begin(), s.end());
        reverse(s.begin(), s.begin() + x);
        reverse(s.begin() + x, s.end());
        return s;
    }

    string add(string s, int x)
    {
        for (int i = 1; i < n; i += 2)
            s[i] = '0' + (s[i] - '0' + x) % 10;
        return s;
    }

public:
    void dfs(string s)
    {
        if (!visited.count(s))
        {
            rv = min(rv, s);
            visited.insert(s);
            dfs(rotate(s, b));
            dfs(add(s, a));
        }
    }

    string findLexSmallestString(string s, int a, int b)
    {
        rv = s;
        this->a = a, this->b = b, this->n = s.size();
        dfs(s);
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.findLexSmallestString("565510", 7, 2);
    cout << r << endl;

    r = sol.findLexSmallestString("43987654", 7, 3);
    cout << r << endl;

    r = sol.findLexSmallestString("5525", 9, 2);
    cout << r << endl;
}