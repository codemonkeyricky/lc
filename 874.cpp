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
    int robotSim(vector<int> &commands, vector<vector<int>> &obstacles)
    {
        set<array<int,2>> obs;
        for (auto &o : obstacles)
            obs.insert({o[1], o[0]});

        vector<int> dir = {0, 1, 0, -1, 0};
        int k = 1, i = 0, j = 0;
        int rv = 0;
        for (auto &c : commands)
        {
            if (c == -1)
                k = (k - 1 + 4) % 4;
            else if (c == -2)
                k = (k + 1) % 4;
            else 
            {
                for (auto kk = 0; kk < c; ++kk)
                {
                    auto ni = i + dir[k + 0];
                    auto nj = j + dir[k + 1];
                    if (obs.count({ni, nj}))
                        break;
                    i = ni, j = nj;
                    rv = max(rv, i * i + j * j);
                }
            }
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.robotSim(vector<int>() = {4, -1, 4, -2, 4}, vector<vector<int>>() = {{2, 4}});
    cout << r << endl;
}