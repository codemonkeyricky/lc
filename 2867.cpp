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
    using ll = long long;
    void dfs(vector<vector<int>> &al, int p, int u, ll &curr, ll &sum, ll &rv)
    {
        ++curr; 
        rv += sum; 
        for (auto &v : al[u])
            if (v != p)
                if (!prime.count(v))
                    dfs(al, u, v, curr, sum, rv);
    }

    set<int> prime;

public:
    long long countPaths(int n, vector<vector<int>> &edges)
    {
        vector<int> cand(n + 1, 1);
        cand[0] = cand[1] = 0;
        for (auto i = 2; i <= n; ++i)
            if (cand[i])
                for (auto j = 2; i * j < cand.size(); ++j)
                    cand[i * j] = 0;

        for (auto i = 2; i < cand.size(); ++i)
            if (cand[i])
                prime.insert(i);

        vector<vector<int>> al(n + 1);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]),
                al[e[1]].push_back(e[0]);

        long long rv = 0, sum, curr;
        for (auto &p : prime)
        {
            sum = curr = 0;
            for (auto &v : al[p])
                if (!prime.count(v))
                {
                    dfs(al, p, v, curr, sum, rv);
                    rv += curr;
                    sum += curr;
                    curr = 0;
                }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPaths(6, vector<vector<int>>() = {{1, 2}, {1, 3}, {2, 4}, {3, 5}, {3, 6}});
    cout << r << endl;

    r = sol.countPaths(5, vector<vector<int>>() = {{1, 2}, {1, 3}, {2, 4}, {2, 5}});
    cout << r << endl;
}