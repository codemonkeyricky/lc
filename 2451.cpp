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
    string oddString(vector<string> &words)
    {
        map<vector<int>, multiset<string>> dp;
        for (auto &w : words)
        {
            vector<int> hash;
            for (auto i = 1; i < w.size(); ++i)
                hash.push_back(w[i] - w[i - 1]);
            dp[hash].insert(w);
        }

        for (auto &d : dp)
            if (d.second.size() == 1)
                return *d.second.begin();
        return "";
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}