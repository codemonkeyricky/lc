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
    int countPairs(vector<vector<int>> &coordinates, int k)
    {
        unordered_map<int, unordered_map<int, int>> coords;
        for (auto &c : coordinates)
            ++coords[c[0]][c[1]];
        
        int n = coordinates.size(), rv = 0;
        for (auto i = 0; i < n; ++i)
        {
            auto &c = coordinates[i];
            --coords[c[0]][c[1]];
            for (auto x_xor = 0; x_xor <= 100; ++x_xor)
            {
                int x2 = x_xor ^ c[0];
                rv += coords[x2][(k - x_xor) ^ c[1]];
            }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPairs(vector<vector<int>>() = {{1, 2}, {4, 2}, {1, 3}, {5, 2}}, 5);
    cout << r << endl;
}