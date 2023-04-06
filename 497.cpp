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
    vector<vector<int>> rects;
    vector<int> area;

public:
    Solution(vector<vector<int>> &rects) : rects(rects)
    {
        area.push_back(0);
        for (auto &r : rects)
            area.push_back(area.back() + (r[3] - r[1] + 1) * (r[2] - r[0] + 1));
    }

    vector<int> pick()
    {
        auto p = rand() % area.back();
        auto k = prev(upper_bound(begin(area), end(area), p)) - begin(area);
        auto pixels = p - area[k];
        auto x = rects[k][0]; 
        auto y = rects[k][1];
        auto h = rects[k][3] - rects[k][1] + 1;
        auto w = rects[k][2] - rects[k][0] + 1;
        return {x + pixels % w, y + pixels / w};
    }

    void count()
    {
        for (auto i = 0; i < area.back(); ++i)
        {
            int k = prev(upper_bound(begin(area), end(area), i)) - begin(area);
            cout << k << " - " ;
            auto pixels = i - area[k];
            auto x = rects[k][0];
            auto y = rects[k][1];
            auto h = rects[k][3] - rects[k][1] + 1;
            auto w = rects[k][2] - rects[k][0] + 1;
            cout << "(" << x + pixels % w << ", " << y + pixels / w << ")" << endl;
        }
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */

int main()
{
    vector<vector<int>> rects = {{82918473, -57180867, 82918476, -57180863}, {83793579, 18088559, 83793580, 18088560}, {66574245, 26243152, 66574246, 26243153}, {72983930, 11921716, 72983934, 11921720}};
    // vector<vector<int>> rects = {{-2, -2, 1, 1}, {2, 2, 4, 6}};
    Solution sol(rects);
    sol.count();
    for(auto i = 0; i < 10; ++i)
    {
        auto r = sol.pick();
        cout << r[0] << ", " << r[1] << endl;
    }
}