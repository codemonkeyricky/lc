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
    struct Trie 
    {
        struct Trie *bits[2] = {};
    };

    Trie *root = nullptr;

    void insert(long long n)
    {
        if (!root)
            root = new Trie();

        auto trie = root;
        int k = 63; 
        while (k >= 0)
        {
            auto b = !!(n & (1ll << k));
            if (!trie->bits[b])
                trie->bits[b] = new Trie();
            trie = trie->bits[b];
            --k;
        }
    }

    long long getMaxXor(long long n)
    {
        auto trie = root;
        long long k = 63, rv = 0;
        while (trie && k >= 0)
        {
            long long b = !(n & (1ll << k));
            if (trie->bits[b])
                rv |= b << k, trie = trie->bits[b];
            else
                rv |= (long long)!b << k, trie = trie->bits[!b];
            --k;
        }
        return k == -1 ? rv ^ n : 0;
    }

    long long dfs(vector<vector<int>> &al, int k, vector<int> &values, vector<int> &seen, vector<long long> &sum)
    {
        seen[k] = true;
        sum[k] += values[k];
        for (auto &n : al[k])
            if (!seen[n])
                sum[k] += dfs(al, n, values, seen, sum);
        return sum[k];
    }

    long long dfs2(vector<vector<int>> &al, int k, vector<int> &seen, vector<long long> &sum)
    {
        long long rv = getMaxXor(sum[k]);
        seen[k] = true;
        for (auto &n : al[k])
            if (!seen[n])
                rv = max(rv, dfs2(al, n, seen, sum));
        insert(sum[k]);
        return rv;
    }

public:
    long long maxXor(int n, vector<vector<int>> &edges, vector<int> &values)
    {
        vector<vector<int>> al(n);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);
        
        vector<int> seen(n);
        vector<long long> sum(n);
        dfs(al, 0, values, seen, sum);

        seen = vector<int>(n);
        return dfs2(al, 0, seen, sum);
    }
};


int main()
{
    Solution sol;
    int r;

    r = sol.maxXor(6, vector<vector<int>>() = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}}, vector<int>() = {2, 8, 3, 6, 2, 5});
    cout << r << endl;
}