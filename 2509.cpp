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
    vector<int> cycleLengthQueries(int n, vector<vector<int>> &queries)
    {
        vector<int> rv;
        for (auto &q : queries)
        {
            int a = q[0], b = q[1];

            int r = 0;
            while (a != b)
            {
                if (a > b)
                    swap(a, b);
                b /= 2; 
                ++r;
            }
            rv.push_back(r + 1);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.cycleLengthQueries(3, vector<vector<int>>() = {{5, 3}, {4, 7}, {2, 3}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}