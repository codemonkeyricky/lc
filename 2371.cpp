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
    vector<vector<int>> minScore(vector<vector<int>> &grid)
    {
        int m = grid.size(); 
        int n = grid[0].size();
        vector<array<int, 3>> v;
        for (auto i = 0; i < m; ++i)
            for (auto j = 0; j < n; ++j)
                v.push_back({grid[i][j], i, j});
        sort(begin(v), end(v));

        vector<int> rows(m), cols(n);

        vector<vector<int>> rv(m, vector<int>(n));
        int k = 0;
        for (auto &[vv, i, j] : v)
        {
            rv[i][j] = max(rows[i], cols[j]) + 1;
            rows[i] = max(rows[i], rv[i][j]); 
            cols[j] = max(cols[j], rv[i][j]); 
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> r;

    r = sol.minScore(vector<vector<int>>() = {{958213553, 391075088, 294041776, 750593666, 570151622}, {941433479, 495349909, 939276712, 636737713, 120598534}, {813768409, 746077739, 479037944, 86155137, 979785043}, {211990723, 226562315, 380218424, 992809774, 293395362}});
    for (auto &rr : r)
    {
        for (auto &c : rr)
            cout << c << " ";
        cout << endl;
    }
    cout << endl;

    r = sol.minScore(vector<vector<int>>() = {{920212616, 142237098, 345501974, 533487831, 269413793, 819692083, 469106291, 483049590, 63489034, 58052923}});
    for(auto & rr: r)
    {
        for (auto &c : rr)
            cout << c << " ";
        cout << endl;
    }
    cout << endl;

    r = sol.minScore(vector<vector<int>>() = {{3, 1}, {2, 5}});
    for(auto & rr: r)
    {
        for (auto &c : rr)
            cout << c << " ";
        cout << endl;
    }
    cout << endl;
}