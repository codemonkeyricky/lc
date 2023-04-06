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
    void dfs(vector<vector<int>> &friends, vector<vector<string>> &watched, int p, int c, int d, int l, map<string, int> &rv)
    {
        if (d == l)
        {
            if (!seen.count(c))
            {
                seen.insert(c);
                for (auto &w : watched[c])
                    ++rv[w];
            }
            return;
        }

        for (auto &f : friends[c])
            if (f != p)
                dfs(friends, watched, c, f, d + 1, l, rv);
    }

    unordered_set<int> seen;

public:
    vector<string> watchedVideosByFriends(vector<vector<string>> &watchedVideos, vector<vector<int>> &friends, int id, int level)
    {
        map<string, int> rv;
        dfs(friends, watchedVideos, -1, id, 0, level, rv);
        vector<pair<int, string>> rv2;
        for (auto &r : rv)
            rv2.push_back({r.second, r.first});
        sort(begin(rv2), end(rv2));

        vector<string> rv3;
        for (auto &r : rv2)
            rv3.push_back(r.second);

        return rv3;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}