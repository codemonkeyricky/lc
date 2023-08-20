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
    string concat(string &a, string &b)
    {
        if (a.size() >= b.size())
            if (a.find(b) != string::npos)
                return a;

        for (int i = min(a.size(), b.size()); i >= 0; --i)
        {
            auto as = a.substr(a.size() - i, i);
            auto bs = b.substr(0, i);
            if (as == bs)
                return a + b.substr(i);
        }
        return a + b;
    }

    string minimal(string &a, string &b, string &c)
    {
        auto aa = concat(a, b);
        return concat(aa, c);
    }

public:
    string minimumString(string a, string b, string c)
    {
        vector<string> r(6);
        r[0] = minimal(a, b, c);
        r[1] = minimal(a, c, b);
        r[2] = minimal(b, a, c);
        r[3] = minimal(b, c, a);
        r[4] = minimal(c, a, b);
        r[5] = minimal(c, b, a);
        string rv = r[0];
        for (auto &rr : r)
            if (rr.size() < rv.size() || (rr.size() == rv.size() && rr < rv))
                rv = rr;
        return rv;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.minimumString("cab", "a", "b");
    cout << r << endl;

    r = sol.minimumString("ca", "a", "a");
    cout << r << endl;

    r = sol.minimumString("abc", "bca", "aaa");
    cout << r << endl;
}