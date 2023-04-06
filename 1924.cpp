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
    vector<double> outerTrees(vector<vector<int>> &t)
    {
        sort(begin(t), end(t));

        int n = t.size();
        long maxSoFar = 0;
        array<int, 2> index;
        for (auto i = 0; i < n; ++i)
            for (auto j = i + 1; j < n; ++j)
            {
                long a = t[i][0] - t[j][0];
                long b = t[i][1] - t[j][1];
                if (a * a + b * b > maxSoFar)
                {
                    maxSoFar = a * a + b * b;
                    index = {i, j};
                }
            }

        int i = index[0], j = index[1];
        double x = ((double)t[i][0] + t[j][0]) / 2;
        double y = ((double)t[i][1] + t[j][1]) / 2;
        long a = t[i][0] - t[j][0];
        long b = t[i][1] - t[j][1];
        double r = sqrt(a * a + b * b) / 2;
        return {x, y, r};
    }
};

int main()
{
    Solution sol;
    int r;

    sol.outerTrees(vector<vector<int>>() = {{55, 7}, {36, 30}, {1, 64}, {83, 97}, {8, 90}, {16, 7}, {18, 23}, {98, 77}, {57, 33}, {98, 54}, {73, 7}});
}