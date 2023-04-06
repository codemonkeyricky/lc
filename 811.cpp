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
public:
    vector<string> subdomainVisits(vector<string> &cpdomains)
    {
        unordered_map<string, int> dp;
        for (auto &domain : cpdomains)
        {
            auto space = domain.find(' ');
            auto k = stoi(domain.substr(0, space));
            auto d = domain.substr(space + 1);
            for (auto i = space + 1; i < domain.size(); ++i)
                if (i == space + 1 || domain[i - 1] == '.')
                    dp[domain.substr(i)] += k;
        }

        vector<string> rv;
        for (auto &d : dp)
            rv.push_back(to_string(d.second) + " " + d.first);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.subdomainVisits(vector<string>() = {"9001 discuss.leetcode.com"});
}