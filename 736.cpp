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
    string getToken(string &expr, int i)
    {
        string token;
        if (expr[i] != '(')
            while (i < expr.size() && expr[i] != ' ' && expr[i] != ')')
                token += expr[i++];
        else
        {
            token += '(';
            int brackets = 1;
            ++i;
            while (i < expr.size() && brackets)
            {
                if (expr[i] == '(')
                    ++brackets;
                else if (expr[i] == ')')
                    --brackets;
                token += expr[i++];
            }
        }
        return token;
    }

public:
    int evaluate(string expr, unordered_map<string, int> table = {})
    {
        if (isdigit(expr[0]) || expr[0] == '-')
            return stoi(expr);
        else if (expr[0] != '(')
            return table[expr];

        int n = expr.size();
        auto space = expr.find(' ');
        auto op = expr.substr(0, space);
        if (op == "(let")
        {
            int i = space + 1;
            while (i < n)
            {
                auto token1 = getToken(expr, i);
                i += token1.size() + 1;
                if (i < n)
                {
                    auto token2 = getToken(expr, i);
                    i += token2.size() + 1;
                    table[token1] = evaluate(token2, table);
                }
                else
                    return evaluate(token1, table);
            }
        }
        else if (op == "(mult")
        {
            int i = space + 1;
            auto token1 = getToken(expr, i);

            i += token1.size() + 1;
            auto token2 = getToken(expr, i);

            return evaluate(token1, table) * evaluate(token2, table);
        }
        else if (op == "(add")
        {
            int i = space + 1;
            auto token1 = getToken(expr, i);

            i += token1.size() + 1;
            auto token2 = getToken(expr, i);

            return evaluate(token1, table) + evaluate(token2, table);
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.evaluate("(let var 78 b 77 (let c 33 (add c (mult var 66))))");
    cout << r << endl;

    r = sol.evaluate("(let x 7 -12)");
    cout << r << endl;

    r = sol.evaluate("(let a1 3 b2 (add a1 1) b2)");
    cout << r << endl;

    r = sol.evaluate("(let x 1 y 2 x (add x y) (add x y))");
    cout << r << endl;

    r = sol.evaluate("(let x 3 x 2 x)");
    cout << r << endl;

    r = sol.evaluate("(let x 2 (mult x (let x 3 y 4 (add x y))))");
    cout << r << endl;
}