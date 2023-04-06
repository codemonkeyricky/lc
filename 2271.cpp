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
    int maximumWhiteTiles(vector<vector<int>> &tiles, int len)
    {
        int n = tiles.size();
        sort(begin(tiles), end(tiles));
        int cnt = 0, rv = 0;
        for (auto i = 0, j = 0; i < n && j < n; ++i, j = max(j, i))
        {
            while (j < n && tiles[i][0] + len - 1 >= tiles[j][1])
                cnt += tiles[j][1] - tiles[j][0] + 1, ++j;

            int partial = 0;
            if (j < n && tiles[i][0] + len - 1 >= tiles[j][0])
                partial += tiles[i][0] + len - 1 - tiles[j][0] + 1;

            rv = max(rv, cnt + partial);

            if (i != j)
                cnt -= tiles[i][1] - tiles[i][0] + 1;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maximumWhiteTiles(vector<vector<int>>() = {{3745, 3757}, {3663, 3681}, {3593, 3605}, {3890, 3903}, {3529, 3539}, {3684, 3686}, {3023, 3026}, {2551, 2569}, {3776, 3789}, {3243, 3256}, {3477, 3497}, {2650, 2654}, {2264, 2266}, {2582, 2599}, {2846, 2863}, {2346, 2364}, {3839, 3842}, {3926, 3935}, {2995, 3012}, {3152, 3167}, {4133, 4134}, {4048, 4058}, {3719, 3730}, {2498, 2510}, {2277, 2295}, {4117, 4128}, {3043, 3054}, {3394, 3402}, {3921, 3924}, {3500, 3514}, {2789, 2808}, {3291, 3294}, {2873, 2881}, {2760, 2760}, {3349, 3362}, {2888, 2899}, {3802, 3822}, {3540, 3542}, {3128, 3142}, {2617, 2632}, {3979, 3994}, {2780, 2781}, {3213, 3233}, {3099, 3113}, {3646, 3651}, {3956, 3963}, {2674, 2691}, {3860, 3873}, {3363, 3370}, {2727, 2737}, {2453, 2471}, {4011, 4031}, {3566, 3577}, {2705, 2707}, {3560, 3565}, {3454, 3456}, {3655, 3660}, {4100, 4103}, {2382, 2382}, {4032, 4033}, {2518, 2531}, {2739, 2749}, {3067, 3079}, {4068, 4074}, {2297, 2312}, {2489, 2490}, {2954, 2974}, {2400, 2418}, {3271, 3272}, {3628, 3632}, {3372, 3377}, {2920, 2940}, {3315, 3330}, {3417, 3435}, {4146, 4156}, {2324, 2340}, {2426, 2435}, {2373, 2376}, {3621, 3626}, {2826, 2832}, {3937, 3949}, {3178, 3195}, {4081, 4082}, {4092, 4098}, {3688, 3698}}, 1638);
    cout << r << endl;

    r = sol.maximumWhiteTiles(vector<vector<int>>() = {{1, 5}, {10, 11}, {12, 18}, {20, 25}, {30, 32}}, 10);
    cout << r << endl;
}