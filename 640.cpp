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
    array<int, 2> convert(string &token)
    {
        int sign = 1; 
        if (token[0] == '-' || token[0] == '+')
        {
            sign = token[0] == '+' ? 1 : -1;
            token = token.substr(1);
        }
        if (token.back() == 'x')
            if (token.size() == 1)
                return {sign, 0};
            else
                return {sign * stoi(token.substr(0, token.size() - 1)), 0};
        return {0, sign * stoi(token)};
    }

    array<int, 2> parse(string &s)
    {
        string token;
        array<int, 2> rv = {};
        for (auto i = 0; i <= s.size(); ++i)
            if (i == s.size() || s[i] == '+' || s[i] == '-')
            {
                if (token.size())
                {
                    auto r = convert(token);
                    rv[0] += r[0], rv[1] += r[1];
                    token.clear();
                }
                if (i < s.size())
                    token += s[i];
            }
            else 
                token += s[i];
        return rv; 
    }

public:
    string solveEquation(string equation)
    {
        if (equation == "x=x")
            return "Infinite solutions";

        auto equal = equation.find('=');
        auto s1 = equation.substr(0, equal);
        auto s2 = equation.substr(equal + 1);
        auto r1 = parse(s1);
        auto r2 = parse(s2);

        if (r1 == r2)
            return "Infinite solutions";

        r1[0] -= r2[0];
        r2[1] -= r1[1];
        if (r1[0] == 0)
            return "No solution";

        return "x=" + to_string(r2[1] / r1[0]);
    }
};


int main()
{
    Solution sol;
    string r;

    r = sol.solveEquation("2+2-x+x+3x=x+2x-x+x+4");
    cout << r << endl;

    r = sol.solveEquation("-x=-1");
    cout << r << endl;

    r = sol.solveEquation("2x+3x-6x=x+2");
    cout << r << endl;

    r = sol.solveEquation("x=x");
    cout << r << endl;

    r = sol.solveEquation("x+5-3+x=6+x-2");
    cout << r << endl;
}