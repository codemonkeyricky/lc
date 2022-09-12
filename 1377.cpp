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
    void dfs(vector<vector<int>> &al, int k, double p, vector<tuple<double, int, bool>> &prob, int ctime, int ttime)
    {
        if (get<0>(prob[k]) == 0)
        {
            get<0>(prob[k]) = p, get<1>(prob[k]) = ctime, get<2>(prob[k]) = (k != 1 && al[k].size() == 1) || (k == 1 && al[k].size() == 0);
            if ((al[k].size() - (k == 1 ? 0 : 1)) && ctime < ttime)
            {
                auto pp = p / (al[k].size() - (k == 1 ? 0 : 1));
                for (auto &n : al[k])
                    if (n != k)
                        dfs(al, n, pp, prob, ctime + 1, ttime);
            }
        }
    }

public:
    double frogPosition(int n, vector<vector<int>> &edges, int t, int target)
    {
        vector<vector<int>> al(n + 1);
        for (auto &e : edges)
            al[e[0]].push_back(e[1]), al[e[1]].push_back(e[0]);

        vector<tuple<double, int, bool>> prob(n + 1);
        dfs(al, 1, 1, prob, 0, t);
        if (t > get<1>(prob[target]) && get<2>(prob[target]))
            return get<0>(prob[target]);
        else if (t == get<1>(prob[target]))
            return get<0>(prob[target]);
        return 0;
    }
};

int main()
{
    Solution sol;
    double r;

    r = sol.frogPosition(9, vector<vector<int>>() = {{2, 1}, {3, 2}, {4, 3}, {5, 3}, {6, 5}, {7, 3}, {8, 4}, {9, 5}}, 9, 1);
    cout << r << endl;

    r = sol.frogPosition(9, vector<vector<int>>() = {{2, 1}, {3, 1}, {4, 2}, {5, 1}, {6, 2}, {7, 5}, {8, 7}, {9, 7}}, 6, 8);
    cout << r << endl;

    r = sol.frogPosition(3, vector<vector<int>>() = {{2, 1}, {1, 3}}, 3, 2);
    cout << r << endl;

    r = sol.frogPosition(1, vector<vector<int>>() = {}, 1, 1);
    cout << r << endl;

    r = sol.frogPosition(7, vector<vector<int>>() = {{1,2},{1,3},{1,7},{2,4},{2,6},{3,5}}, 20, 6);
    cout << r << endl;

    // r = sol.frogPosition(3, vector<vector<int>>() = {{2, 1}, {3, 2}}, 1, 2);
    // cout << r << endl;

    r = sol.frogPosition(7, vector<vector<int>>() = {{1, 2}, {1, 3}, {1, 7}, {2, 4}, {2, 6}, {3, 5}}, 2, 4);
    cout << r << endl;
}