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
    std::string replaceStr(std::string subject,
                           const std::string &search,
                           const std::string &replace)
    {
        size_t pos = 0;
        while ((pos = subject.find(search, pos)) != std::string::npos)
        {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
        return subject;
    }

    vector<pair<string, int>> multiply(vector<pair<string, int>> &a, vector<pair<string, int>> &b)
    {
        vector<pair<string, int>> rv;
        for (auto &aa : a)
            for (auto &bb : b)
                if (aa.first.size() && bb.first.size())
                    rv.push_back({aa.first + "*" + bb.first, aa.second * bb.second});
                else
                    rv.push_back({max(aa.first, bb.first), aa.second * bb.second});
        return rv;
    }

    pair<string, int> normalize(string &token)
    {
        int sign = 1;
        if (token[0] == '-')
            sign = -1, token = token.substr(1);
        else if (token[0] == '+')
            token = token.substr(1);

        if (isdigit(token[0]))
            return {"", sign * stoi(token)};
        else
            return {token, sign};
    }

    vector<pair<string, int>> expand(string &expr)
    {
        int n = expr.size();
        vector<vector<pair<string, int>>> rv;
        string token;
        for (auto i = 0; i < n; ++i)
            if (expr[i] == '(')
            {
                int brackets = 1;
                string subexpr;
                ++i;
                while (i < n && brackets)
                {
                    if (expr[i] == '(')
                        ++brackets;
                    else if (expr[i] == ')')
                        --brackets;
                    subexpr += expr[i++];
                }
                subexpr.pop_back();
                --i;
                auto b = expand(subexpr);
                if (rv.size() && rv.back().back().first == "*")
                {
                    rv.pop_back();
                    auto a = rv.back();
                    rv.pop_back();
                    rv.push_back(multiply(a, b));
                }
                else
                    rv.push_back(b);

                if (token.size() && token[0] == '-')
                    for (auto &c : rv.back())
                        c.second *= -1;
                token.clear();
            }
            else if (expr[i] == ')')
                goto finalize;
            else if (expr[i] == '*' || expr[i] == '+' || expr[i] == '-')
            {
                if (token.size())
                {
                    vector<pair<string, int>> b = {normalize(token)};
                    if (rv.size() && rv.back().back().first == "*")
                    {
                        rv.pop_back();
                        auto a = rv.back();
                        rv.pop_back();
                        rv.push_back(multiply(a, b));
                    }
                    else
                        rv.push_back(b);
                }

                token.clear();
                if (expr[i] == '*')
                {
                    vector<pair<string, int>> push = {{"*", 0}};
                    rv.push_back(push);
                }
                else
                    token += expr[i];
            }
            else
                token += expr[i];

finalize:
        if (token.size())
        {
            vector<pair<string, int>> b = {normalize(token)};
            if (rv.size() && rv.back().back().first == "*")
            {
                rv.pop_back();
                auto a = rv.back();
                rv.pop_back();
                rv.push_back(multiply(a, b));
            }
            else
                rv.push_back(b);
        }

        vector<pair<string, int>> rrv;
        for (auto &r : rv)
            for (auto &rr : r)
                rrv.push_back(rr);
        return rrv;
    }

    string normalize2(string s)
    {
        vector<string> coeff; 
        string token;
        for (auto i = 0; i <= s.size(); ++i)
            if (i == s.size() || s[i] == '*')
                coeff.push_back(token), token.clear();
            else
                token += s[i];
        sort(begin(coeff), end(coeff));
        string rv;
        for (auto i = 0; i + 1 < coeff.size(); ++i)
            rv += coeff[i] + "*";
        rv += coeff.back();
        return rv;
    }

public:
    vector<string> basicCalculatorIV(string expr, vector<string> &vars, vector<int> &vals)
    {
        unordered_map<string, string> table;
        for (auto i = 0; i < vars.size(); ++i)
            table[vars[i]] = to_string(vals[i]);

        string expr2, token;
        for (auto i = 0; i <= expr.size(); ++i)
        {
            if (i == expr.size() || expr[i] == '(' || expr[i] == ')' || expr[i] == '*' || expr[i] == '-' || expr[i] == '+')
            {
                if (token.size())
                {
                    if (!table.count(token))
                        expr2 += token;
                    else
                        expr2 += table[token];
                    token.clear();
                }

                if (i < expr.size())
                    expr2 += expr[i];
            }
            else if (expr[i] == ' ')
                ;
            else
                token += expr[i];
        }
        swap(expr, expr2);

        expr2.clear();
        for (auto i = 0; i < expr.size(); ++i)
            if (i < expr.size() && expr[i] == '+' && expr[i + 1] == '-')
                expr2 += '-', ++i;
            else if (i < expr.size() && expr[i] == '-' && expr[i + 1] == '+')
                expr2 += '-', ++i;
            else if (i < expr.size() && expr[i] == '-' && expr[i + 1] == '-')
                expr2 += '+', ++i;
            else
                expr2 += expr[i];
        swap(expr2, expr);

        auto parsed = expand(expr);
        map<string, int> map;
        for (auto &p : parsed)
            map[normalize2(p.first)] += p.second;

        vector<pair<string, int>> rv;
        for (auto &m : map)
            if (m.second)
                rv.push_back({m.first, m.second});

        sort(begin(rv), end(rv), [](pair<string, int> &l, pair<string, int> &r)
             {
                 auto a = count_if(begin(l.first), end(l.first), [](char &c)
                                   { return c == '*'; });
                 auto b = count_if(begin(r.first), end(r.first), [](char &c)
                                   { return c == '*'; });
                 a += l.first.size() ? 1 : 0;
                 b += r.first.size() ? 1 : 0;
                 if (a > b)
                     return true;
                 else if (a < b)
                     return false;
                 return l.first < r.first;
             });

        vector<string> rrv;
        for (auto &r : rv)
            if (r.first.size())
                rrv.push_back(to_string(r.second) + "*" + r.first);
            else
                rrv.push_back(to_string(r.second));

        return rrv;
    }
};

int main()
{
    Solution sol;
    vector<string> r;

    r = sol.basicCalculatorIV("(av * 9) - (ar + 0) - ((bq - cv) + v * (b + bq - bk)) * (a - 12 + 2 - (6 * cc - 8 - bv + ag))",
                              vector<string>() = {"d", "g", "h", "j", "l", "o", "s", "u", "v", "w", "af", "ag", "ah", "ak", "at", "au", "av", "aw", "az", "bc", "be", "bg", "bj", "bm", "bn", "bq", "br", "bs", "bt", "bu", "bv", "bw", "bx", "by", "bz", "ca", "cd", "ce", "cf", "ch", "ci", "ck", "cq", "cr", "cs", "cu", "cv"},
                              vector<int>() = {3, 6, 7, 9, 11, 1, 5, 7, 8, 9, 10, 11, 12, 2, 11, 12, 0, 1, 4, 12, 1, 3, 6, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 5, 6, 7, 9, 10, 12, 5, 6, 7, 9, 10});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.basicCalculatorIV("a + b", vector<string>() = {"a", "b"}, vector<int>() = {10, -7});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.basicCalculatorIV("((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))", vector<string>() = {}, vector<int>() = {});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.basicCalculatorIV("a * b * c + b * a * c * 4", vector<string>() = {}, vector<int>() = {});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.basicCalculatorIV("e - 8 + temperature - pressure", vector<string>() = {"e", "temperature"}, vector<int>() = {1, 12});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.basicCalculatorIV("(e + 8) * (e - 8)", vector<string>() = {}, vector<int>() = {});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}