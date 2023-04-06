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
    bool isDecimal(string &s)
    {
        auto p = s.find('.');
        if (p == string::npos)
            return isInteger(s);
        
        auto prefix = s.substr(0, p);
        auto suffix = s.substr(p + 1);
        if (prefix == "" && suffix == "")
            return false;
        if (suffix.size() && (suffix[0] == '+' || suffix[0] == '-'))
            return false;
        if ((prefix == "+" || prefix == "-") && suffix == "")
            return false;
        return isInteger(prefix) && isInteger(suffix);
    }

    bool isInteger(string &s, bool sign_support = true)
    {
        if (s.empty())
            return true;


        int i = 0;
        if (sign_support)
            if (s[0] == '+' || s[0] == '-')
                ++i;

        for (; i < s.size(); ++i)
            if (!isdigit(s[i]))
                return false;
        return true;
    }

    bool isEmpty(string &c)
    {
        if (c.empty())
            return true;
        if (c == "+" || c == "-")
            return true;
        return false;
    }

public:
    bool isNumber(string s)
    {
        if (s == "+" || s == "-")
            return false;

        for (auto &c : s)
            c = tolower(c);

        auto p = s.find('e');
        if (p != string::npos)
        {
            auto prefix = s.substr(0, p);
            auto suffix = s.substr(p + 1);
            if (isEmpty(prefix) || isEmpty(suffix)) 
                return false;
            return (isDecimal(prefix) || isInteger(prefix)) && isInteger(suffix);
        }
        return isDecimal(s);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isNumber("+");
    cout << r << endl;

    r = sol.isNumber("005047e+6");
    cout << r << endl;

    r = sol.isNumber("+.");
    cout << r << endl;

    r = sol.isNumber("+.8");
    cout << r << endl;

    r = sol.isNumber(".1");
    cout << r << endl;
}