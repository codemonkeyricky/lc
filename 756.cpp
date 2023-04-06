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
    bool dfs(vector<string> &layers, int l, int k, unordered_map<string, vector<string>> &map)
    {
        if (layers[l].size() == 1)
            return true;

        if (k + 1 >= layers[l].size())
            return dfs(layers, l + 1, 0, map);

        if (!dp.count(layers[l]))
            dp[layers[l]] = vector<int>(layers[0].size());

        if (!dp[layers[l]][k])
        {
            int rv = 0;
            for (auto &s : map[layers[l].substr(k, 2)])
            {
                layers[l + 1] += s;
                if (dfs(layers, l, k + 1, map))
                {
                    rv = 1;
                    break;
                }
                layers[l + 1].pop_back();
            }
            dp[layers[l]][k] = rv + 1;
        }
        return dp[layers[l]][k] - 1;
    }

    unordered_map<string, vector<int>> dp;

public:
    bool pyramidTransition(string bottom, vector<string> &allowed)
    {
        unordered_map<string, vector<string>> map;
        for (auto &allow : allowed)
            map[allow.substr(0, 2)].push_back(allow.substr(2));
        
        vector<string> layers(bottom.size());
        layers[0] = bottom;

        return dfs(layers, 0, 0, map);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.pyramidTransition("CBDDA", vector<string>() = {"ACC", "ACA", "AAB", "BCA", "BCB", "BAC", "BAA", "CAC", "BDA", "CAA", "CCA", "CCC", "CCB", "DAD", "CCD", "DAB", "ACD", "DCA", "CAD", "CBB", "ABB", "ABC", "ABD", "BDB", "BBC", "BBA", "DDA", "CDD", "CBC", "CBA", "CDA", "DBA", "ABA"});
    cout << r << endl;

    r = sol.pyramidTransition("AAAA", vector<string>() = {"AAB", "AAC", "BCD", "BBE", "DEF"});
    cout << r << endl;

    r = sol.pyramidTransition("BCD", vector<string>() = {"BCC", "CDE", "CEA", "FFF"});
    cout << r << endl;
}