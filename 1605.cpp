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

using mat = vector<vector<int>>;
using vec = vector<int>;

class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int> &rs, vector<int> &cs)
    {
        mat m(rs.size(), vec(cs.size()));
        for (auto x = 0; x < rs.size(); ++x)
            for (auto y = 0; y < cs.size(); ++y)
            {
                m[x][y] = min(rs[x], cs[y]);
                rs[x] -= m[x][y];
                cs[y] -= m[x][y];
            }
        return m;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.restoreMatrix(vector<int>() = {3, 8}, vector<int>() = {4, 7});
    cout << r << endl;
}