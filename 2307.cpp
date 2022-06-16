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
    bool bellmanFord(const vector<vector<double>> &g, int k)
    {
        vector<double> dist(g.size(), INT_MAX);
        dist[k] = 0;
        bool update = false;
        for (auto times = 1; times < g.size(); ++times)
        {
            for (auto i = 0; i < g.size(); ++i)
                for (auto j = 0; j < g[i].size(); ++j)
                    if (g[i][j] != INT_MAX && dist[i] != INT_MAX && dist[j] > dist[i] + g[i][j])
                        update = true, dist[j] = dist[i] + g[i][j];

            if (!update)
                return false;
        }

        for (auto i = 0; i < g.size(); ++i)
            for (auto j = 0; j < g[i].size(); ++j)
                if (g[i][j] != INT_MAX && dist[i] != INT_MAX && dist[j] - (dist[i] + g[i][j]) > 0.00001)
                    return true;
        return false;
    }

public:
    bool checkContradictions(vector<vector<string>> &equations, vector<double> &values)
    {
        unordered_map<string, int> lookup;
        int count = 0;
        for (auto &eq : equations)
        {
            if (!lookup.count(eq[0]))
                lookup[eq[0]] = count++;
            if (!lookup.count(eq[1]))
                lookup[eq[1]] = count++;
        }

        vector<vector<double>> currency(count, vector<double>(count, INT_MAX));
        for (auto i = 0; i < equations.size(); ++i)
        {
            auto a = lookup[equations[i][0]];
            auto b = lookup[equations[i][1]];

            double c = -log10(values[i]);
            if (currency[a][b] == INT_MAX || abs(c - currency[a][b]) <= 0.00001)
                currency[a][b] = c; 
            else 
                return true;

            c = -log10(1.0f / values[i]);
            if (currency[b][a] == INT_MAX || abs(c - currency[b][a]) <= 0.00001)
                currency[b][a] = c;
            else
                return true;
        }

        for (auto i = 0; i < count; ++i)
            if (!bellmanFord(currency, i))
                return false;
        return true;
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