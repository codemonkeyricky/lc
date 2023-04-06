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
    string getSuffix(string &a, int even)
    {
        vector<char> lookup = {'0', '1', 'x', 'x', 'x', 'x', '9', 'x', '8', '6'};
        string rv;
        for (auto it = !even ? next(rbegin(a)) : rbegin(a); it != rend(a); ++it)
            rv += lookup[*it - '0'];
        return rv; 
    }

    void dfs(string &prefix, long low, long high, set<long> &rv)
    {
        if (prefix.size())
        {
            for (auto i = 0; i < 2; ++i)
            {
                if (i == 0 && (prefix.back() == '6' || prefix.back() == '9'))
                    continue;

                string concat = prefix + getSuffix(prefix, i);
                auto k = stol(concat);
                if (i == 1 && k > high)
                    return;
                if (low <= k && k <= high)
                    rv.insert(k);
            }
        }

        vector<char> strobes = {'0', '1', '8', '6', '9'};
        for (auto i = 0; i < strobes.size(); ++i)
        {
            if (prefix.empty() || prefix[0] != '0')
            {
                prefix.push_back(strobes[i]);
                dfs(prefix, low, high, rv);
                prefix.pop_back();
            }
        }
    }

public:
    int strobogrammaticInRange(string low, string high)
    {
        string curr;
        set<long> rv;
        dfs(curr, stol(low), stol(high), rv);
        return rv.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.strobogrammaticInRange("0", "200");
    cout << r << endl;

    r = sol.strobogrammaticInRange("0", "0");
    cout << r << endl;

    r = sol.strobogrammaticInRange("50", "100");
    cout << r << endl;
}