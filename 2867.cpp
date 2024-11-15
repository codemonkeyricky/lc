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

    int dfs(vector<vector<int>> &al, int p, int u, set<int> &prime_visited)
    {
        np_visited.insert(u);
        int rv = 1;
        for (auto &v : al[u])
            if (v != p)
                if (prime.count(v))
                    prime_visited.insert(v);
                else 
                    rv += dfs(al, u, v, prime_visited); 
        return rv; 
    }

    set<int> prime, np_visited;

public:
    long long countPaths(int n, vector<vector<int>> &edges)
    {
        prime.clear();

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

        set<int> not_prime;
        for (auto &e : edges)
            for (auto k = 0; k < 2; ++k)
                if (!prime.count(e[k]))
                    not_prime.insert(e[k]);

        vector<vector<int>> al_cnt(n + 1);
        np_visited.clear();
        for (auto &np : not_prime)
        {
            if (!np_visited.count(np))
            {
                set<int> prime_visited;
                int visited = dfs(al, -1, np, prime_visited);
                for (auto &p : prime_visited)
                    al_cnt[p].push_back(visited);
            }
        }

        long long rv = 0, sum, curr;
        for (auto &p : prime)
        {
            sum = curr = 0;
            for (auto &v : al_cnt[p])
            {
                rv += sum * v + v; 
                sum += v; 
            }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPaths(5, vector<vector<int>>() = {{4, 1}, {5, 4}, {2, 1}, {3, 4}});
    cout << r << endl;

    r = sol.countPaths(1, vector<vector<int>>() = {});
    cout << r << endl;

    r = sol.countPaths(6, vector<vector<int>>() = {{1, 2}, {1, 3}, {2, 4}, {3, 5}, {3, 6}});
    cout << r << endl;

    r = sol.countPaths(5, vector<vector<int>>() = {{1, 2}, {1, 3}, {2, 4}, {2, 5}});
    cout << r << endl;
}