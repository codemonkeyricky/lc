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
    void dfs(string &s, string &curr, int k, unordered_map<string, int> &sub)
    {
        if (k >= s.size())
        {
            ++sub[curr];
            return;
        }

        dfs(s, curr, k + 1, sub);
        curr.push_back(s[k]);
        dfs(s, curr, k + 1, sub);
        curr.pop_back();
    }

public:
    int findLUSlength(vector<string> &strs)
    {
        unordered_map<string, int> sub;
        string ref;
        for (auto &s : strs)
            dfs(s, ref, 0, sub);
        
        int rv = -1;
        for (auto &s : sub)
            if (s.second == 1)
                rv = max(rv, (int)s.first.size());
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}