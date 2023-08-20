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
    int dfs(string &s, int k, unordered_set<string> &dict)
    {
        int n = s.size();
        if (k >= n)
            return 0;

        string word;
        if (!dp[k])
        {
            int rv = 1e9;
            for (auto i = k; i < s.size(); ++i)
            {
                word += s[i];
                if (dict.count(word))
                    rv = min(rv, dfs(s, i + 1, dict));
            }
            rv = min(rv, 1 + dfs(s, k + 1, dict));
            dp[k] = rv + 1;
        }
        return dp[k] - 1;
    }

    vector<int> dp;

public:
    int minExtraChar(string s, vector<string> &dictionary)
    {
        unordered_set<string> dict(begin(dictionary), end(dictionary));
        dp = vector<int>(s.size());
        return dfs(s, 0, dict);
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minExtraChar("leetscode", vector<string>() = {"leet", "code", "leetcode"});
    cout << r << endl;

    // r = sol.minExtraChar("ecolloycollotkvzqpdaumuqgs", vector<string>() = {"flbri", "uaaz", "numy", "laper", "ioqyt", "tkvz", "ndjb", "gmg", "gdpbo", "x", "collo", "vuh", "qhozp", "iwk", "paqgn", "m", "mhx", "jgren", "qqshd", "qr", "qpdau", "oeeuq", "c", "qkot", "uxqvx", "lhgid", "vchsk", "drqx", "keaua", "yaru", "mla", "shz", "lby", "vdxlv", "xyai", "lxtgl", "inz", "brhi", "iukt", "f", "lbjou", "vb", "sz", "ilkra", "izwk", "muqgs", "gom", "je"});
    // cout << r << endl;
}