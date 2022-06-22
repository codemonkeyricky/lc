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
#include <climits>

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
public:
    vector<int> parent;
    vector<double> value;
    unordered_map<string, int> mp;
    int n = 0;

    pair<int, double> find(int k)
    {
        if (parent[k] == k)
            return {k, value[k]};

        auto p = find(parent[k]);
        parent[k] = p.first;
        value[k] = value[k] * p.second;
        return {parent[k], value[k]};
    }

    int getId(string &s)
    {
        if (!mp.count(s))
        {
            mp[s] = n;
            parent.push_back(n);
            value.push_back(1.0);
            n++;
        }
        return mp[s];
    }

    void unionize(int a, int b, double d)
    {
        parent[a] = b;
        value[a] = d;
    }

    bool equal(double a, double b)
    {
        static const double er = (1e-9);
        return fabs(a / b - 1.0) < er;
    }

    bool checkContradictions(vector<vector<string>> &equations, vector<double> &values)
    {
        for (int i = 0; i < equations.size(); i++)
        {
            auto &e = equations[i];
            int x = getId(e[0]);
            int y = getId(e[1]);
            double d = values[i];
            auto a = find(x);
            auto b = find(y);
            if (a.first != b.first)
                unionize(a.first, b.first, b.second * d / a.second);
            else
            {
                if (!equal(a.second, b.second * d))
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.checkContradictions(vector<vector<string>>() = {{"s", "b"}, {"b", "b"}, {"u", "js"}, {"zc", "s"}, {"aa", "zvi"}, {"zvi", "eg"}, {"zvi", "drg"}, {"fnopz", "s"}, {"ehhst", "u"}, {"zvi", "drg"}, {"fnopz", "drg"}, {"js", "b"}, {"zc", "eg"}, {"u", "u"}, {"zc", "zc"}, {"u", "eg"}, {"u", "ehhst"}, {"zc", "s"}, {"eg", "zc"}, {"eg", "ifk"}, {"b", "drg"}, {"u", "u"}, {"ehhst", "aa"}, {"eg", "fnopz"}, {"eg", "s"}, {"u", "u"}, {"zvi", "zvi"}, {"zvi", "zc"}, {"drg", "aa"}, {"fnopz", "ifk"}, {"eg", "zc"}, {"ehhst", "s"}, {"b", "ifk"}, {"fnopz", "ifk"}, {"b", "u"}, {"drg", "eg"}, {"u", "eg"}}, vector<double>() = {10.0, 1, 15.625, 3.2, 10.0, 6.25, 16.0, 10.0, 12.5, 16.0, 4.0, 0.64, 0.5, 1, 1, 0.15625, 0.08, 3.2, 2.0, 8.0, 0.04, 1, 0.03125, 0.64, 6.4, 1, 1, 12.5, 0.00625, 12.5, 2.0, 12.5, 0.125, 12.5, 0.1, 0.390625, 0.15625});
    cout << r << endl;

    r = sol.checkContradictions(vector<vector<string>>() = {{"a", "a"}, {"b", "c"}, {"a", "c"}}, vector<double>() = {0.5, 4, 1});
    cout << r << endl;

    r = sol.checkContradictions(vector<vector<string>>() = {{"a", "b"}, {"b", "c"}, {"a", "c"}}, vector<double>() = {0.5, 4, 1});
    cout << r << endl;

    r = sol.checkContradictions(vector<vector<string>>() = {{"omy", "ibef"}, {"r", "dkmq"}}, vector<double>() = {12.5, 3.125});
    cout << r << endl;

    r = sol.checkContradictions(vector<vector<string>>() = {{"le", "et"}, {"le", "code"}, {"code", "et"}}, vector<double>() = {2, 5, 0.5});
    cout << r << endl;

    r = sol.checkContradictions(vector<vector<string>>() = {{"a", "b"}, {"b", "c"}, {"a", "c"}}, vector<double>() = {3, 0.5, 1.5});
    cout << r << endl;
}