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
    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries)
    {
        int m = grid.size();
        int n = grid[0].size();
        priority_queue<array<int, 3>> q;
        vector<int> sum(1000001);
        vector<vector<int>> seen(m, vector<int>(n));
        q.push({-grid[0][0], 0, 0});
        seen[0][0] = true;
        vector<int> off = {0, 1, 0, -1, 0};
        for (auto k = 0; k < 1000001; ++k)
            while (q.size() && -q.top()[0] < k)
            {
                auto [nn, i, j] = q.top();
                ++sum[k];
                q.pop();
                for (auto kk = 0; kk < 4; ++kk)
                {
                    auto ni = i + off[kk + 0];
                    auto nj = j + off[kk + 1];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && !seen[ni][nj])
                        ++seen[ni][nj], q.push({-grid[ni][nj], ni, nj});
                }
            }

        vector<int> dp(sum.size());
        for(auto i = 1; i < dp.size(); ++i)
            dp[i] += sum[i] + dp[i - 1];

        vector<int> rv;
        for (auto &q : queries)
            rv.push_back(dp[q]);

        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.maxPoints(vector<vector<int>>() = {{658239, 430894, 245356, 693645, 194864, 252269, 327182, 895591, 621084, 55305, 998606, 177571, 427284, 244018, 219527, 32836, 530773, 994850}, {903297, 717509, 621469, 818968, 682742, 850059, 471498, 51961, 232723, 66416, 21564, 802233, 969735, 246653, 526661, 381556, 226478, 561618}, {918713, 697757, 524699, 684891, 1152, 165318, 696526, 620938, 297773, 212179, 482128, 864002, 316087, 921682, 595335, 188300, 218873, 166851}, {477368, 670849, 716244, 407245, 412591, 780753, 991252, 806413, 702423, 525270, 800774, 779552, 84541, 431521, 737881, 836878, 972828, 825220}, {591794, 140870, 279453, 765343, 937450, 916783, 704763, 115067, 646098, 572440, 402048, 464939, 912258, 79184, 656992, 910621, 888550, 687667}}, vector<int>() = {184764, 394222, 270489, 373442, 229852, 343258, 47727, 360782});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.maxPoints(vector<vector<int>>() = {{1, 2, 3}, {2, 5, 7}, {3, 5, 1}}, vector<int>() = {5, 6, 2});
    for(auto &c : r)
        cout << c << ", ";
    cout << endl;
        }