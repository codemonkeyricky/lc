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
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>> &queries)
    {
        map<int, vector<int>> bits; ///< sig / [index]
        for (auto i = 0; i < queries.size(); ++i)
            bits[queries[i][0] ^ queries[i][1]].push_back(i);

        vector<vector<int>> rv(queries.size(), {-1, -1});
        for (long k = 0, mask = 0; k < 32; ++k, mask = 0)
            for (long i = 0, j = 0; j < s.size(); ++j)
            {
                mask = (mask << 1) | (s[j] == '1');
                mask &= (1l << (k + 1)) - 1;
                if (bits.count(mask))
                    for (auto &b : bits[mask])
                        if (j - k >= 0)
                            if (rv[b][0] == -1)
                                rv[b] = {(int)(j - k), (int)j};
            }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.substringXorQueries("111010110", vector<vector<int>>() = {{3, 3}});

    sol.substringXorQueries("101101", vector<vector<int>>() = {{0, 5}, {1, 2}});
}