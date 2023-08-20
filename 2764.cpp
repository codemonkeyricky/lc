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
    bool isPreorder(vector<vector<int>> &nodes)
    {
        if (nodes[0][1] != -1)
            return false;

        vector<int> parent;
        parent.push_back(nodes[0][0]);
        for (auto i = 1; i < nodes.size(); ++i)
        {
            auto c = nodes[i][0]; 
            auto p = nodes[i][1];
            while (parent.size() && p != parent.back())
                parent.pop_back();
            if (parent.empty())
                return false;
            parent.push_back(c);
        }
        return true;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.isPreorder(vector<vector<int>>() = {{0, -1}, {1, 0}, {2, 0}, {3, 2}, {4, 2}});
    cout << r << endl;
}