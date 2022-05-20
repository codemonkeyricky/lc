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
    vector<int> bestCoordinate(vector<vector<int>> &towers, int radius)
    {
        sort(begin(towers), end(towers));
        vector<int> rv(2);
        int rq = 0;
        int n = towers.size();
        for (auto i = 0; i < 51; ++i)
            for (auto j = 0; j < 51; ++j)
            {
                double r = 0;
                for (auto &t : towers)
                {
                    auto x = t[0], y = t[1], q = t[2];
                    if ((x - i) * (x - i) + (y - j) * (y - j) <= radius * radius)
                    {
                        double d = sqrt((x - i) * (x - i) + (y - j) * (y - j));
                        r += (int)((double)q / ((double)1 + d));
                    }
                }
                if (r > rq)
                    rq = r, rv = {i, j};
                else if(r == rq)
                    rv = min(rv, {i, j});
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;


    r = sol.bestCoordinate(vector<vector<int>>() = {{30,34,31},{10,44,24},{14,28,23},{50,38,1},{40,13,6},{16,27,9},{2,22,23},{1,6,41},{34,22,40},{40,10,11}}, 20);

    r = sol.bestCoordinate(vector<vector<int>>() = {{44, 31, 4}, {47, 27, 27}, {7, 13, 0}, {13, 21, 20}, {50, 34, 18}, {47, 44, 28}}, 13);
}