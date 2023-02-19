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
    void compose(string s11, string s12, string s21, string s22, vector<string> &rv)
    {
        if (s11[0] == '0' && s11.size() > 1)
            return;

        if (s21[0] == '0' && s21.size() > 1)
            return;

        if (s12.back() == '0' || s22.back() == '0')
            return;

        string r; 
        r += "(" + s11;
        if (s12.size())
            r += "." + s12;
        r += ", " + s21;
        if (s22.size())
            r += "." + s22;
        r += ")"; 
        rv.push_back(r);
    }

    void dfs(string s1, string s2, vector<string> &rv)
    {
        for (auto i = 1; i <= s1.size(); ++i)
            for (auto j = 1; j <= s2.size(); ++j)
                compose(s1.substr(0, i), s1.substr(i), s2.substr(0, j), s2.substr(j), rv);
    }

public:
    vector<string> ambiguousCoordinates(string s)
    {
        auto ss = s.substr(1, s.size() - 2);
        vector<string> rv;
        for (auto i = 1; i < ss.size(); ++i)
            dfs(ss.substr(0, i), ss.substr(i), rv);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.ambiguousCoordinates("(123)");
    cout << r << endl;
}