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
    string normalize(string &s)
    {
        int i;
        string sp, sr;
        for (i = 0; i < s.size() && s[i] != '('; ++i)
            sp += s[i];
        for (++i; i < s.size() && s[i] != ')'; ++i)
            sr += s[i];

        if (sr.empty())
            return sp;

        string temp = sp + sr + sr;
        int len, found = false;
        string real, repeat;
        for (i = 0; i < temp.size() && real.empty(); ++i)
            for (len = 1; i + len * 2 <= temp.size(); ++len)
            {
                bool match = true;
                for (auto k = 1; i + (k + 1) * len <= temp.size(); ++k)
                {
                    auto a = temp.substr(i + (k - 1) * len, len);
                    auto b = temp.substr(i + (k)*len, len);
                    if (a != b)
                    {
                        match = false;
                        break;
                    }
                }

                if (match)
                {
                    real = temp.substr(0, i); 
                    repeat = temp.substr(i, len);
                    break;
                }
            }

        if (repeat != "9")
            return real + (repeat != "0" ? "(" + repeat + ")" : "");
        else 
        {
            string rv;
            int carry = 1;
            for (int i = real.size() - 1, carry = 1; i >= 0; --i)
                if (carry)
                {
                    if (real[i] == '.')
                        rv.push_back('.');
                    else if (real[i] == '9')
                        rv.push_back('0');
                    else
                        rv.push_back(real[i] + 1), carry = 0;
                }
                else
                    rv.push_back(real[i]);

            reverse(begin(rv), end(rv));
            return rv;
        }
    }

public:
    bool isRationalEqual(string s, string t)
    {
        auto a = normalize(s);
        while(a.back() == '0' || a.back() == '.')
            a.pop_back();

        auto b = normalize(t);
        while(b.back() == '0' || b.back() == '.')
            b.pop_back();
        cout << a << endl;
        cout << b << endl;
        return a == b;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isRationalEqual("0.(0)", "0");
    cout << r << endl;

    r = sol.isRationalEqual("0.9(9)", "1.");
    cout << r << endl;

    r = sol.isRationalEqual("0.1666(6)", "0.1666(66)");
    cout << r << endl;

    r = sol.isRationalEqual("0.(52)", "0.5(25)");
    cout << r << endl;
}