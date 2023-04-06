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
    vector<bool> canEat(vector<int> &candies, vector<vector<int>> &queries)
    {
        int n = candies.size();
        vector<long long> sum(n + 1);
        for (auto i = 0; i < n; ++i)
            sum[i + 1] = sum[i] + candies[i];

        vector<bool> rv;
        for (auto &q : queries)
        {
            long long candy = q[0], day = q[1], cap = q[2];
            if (sum[candy + 1] > day && sum[candy] < cap * (day + 1))
                rv.push_back(true);
            else
                rv.push_back(false);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<bool> r;

    r = sol.canEat(vector<int>() = {7, 11, 5, 3, 8}, vector<vector<int>>() = {{2, 2, 6}, {4, 2, 4}, {2, 13, 1000000000}});
    for (auto c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.canEat(vector<int>() = {46, 5, 47, 48, 43, 34, 15, 26, 11, 25, 41, 47, 15, 25, 16, 50, 32, 42, 32, 21, 36, 34, 50, 45, 46, 15, 46, 38, 50, 12, 3, 26, 26, 16, 23, 1, 4, 48, 47, 32, 47, 16, 33, 23, 38, 2, 19, 50, 6, 19, 29, 3, 27, 12, 6, 22, 33, 28, 7, 10, 12, 8, 13, 24, 21, 38, 43, 26, 35, 18, 34, 3, 14, 48, 50, 34, 38, 4, 50, 26, 5, 35, 11, 2, 35, 9, 11, 31, 36, 20, 21, 37, 18, 34, 34, 10, 21, 8, 5}, vector<vector<int>>() = {{85, 54, 42}, {12, 301, 3}, {62, 2016, 29}, {45, 2316, 37}, {43, 2360, 28}, {87, 192, 98}, {27, 2082, 21}, {74, 762, 37}, {51, 35, 17}, {73, 2193, 4}, {60, 425, 65}, {11, 1522, 58}, {21, 1699, 66}, {42, 1473, 5}, {30, 2010, 48}, {91, 796, 74}, {82, 2162, 31}, {23, 2569, 65}, {24, 684, 23}, {70, 1219, 51}, {5, 1817, 15}, {81, 2446, 34}, {96, 771, 60}, {49, 1171, 60}, {41, 567, 67}, {39, 799, 59}, {90, 957, 81}, {84, 2122, 27}, {82, 1707, 44}, {11, 1889, 20}, {80, 1697, 83}, {24, 1786, 60}, {90, 1847, 99}, {51, 114, 21}, {44, 466, 85}, {56, 469, 20}, {44, 350, 96}, {66, 1946, 10}, {14, 2470, 12}, {69, 1175, 18}, {98, 1804, 25}, {77, 2187, 40}, {89, 2265, 45}, {19, 2246, 45}, {40, 2373, 79}, {60, 2222, 17}, {37, 385, 5}, {97, 1759, 97}, {10, 903, 5}, {87, 842, 45}, {74, 2398, 66}, {62, 49, 94}, {48, 156, 77}, {76, 2310, 80}, {64, 2360, 95}, {70, 1699, 83}, {39, 1241, 66}, {92, 2312, 21}, {63, 2148, 29}, {95, 594, 74}, {89, 90, 51}, {82, 137, 70}, {54, 301, 97}, {15, 819, 43}, {47, 1402, 60}, {17, 2377, 43}, {50, 1937, 95}, {62, 1174, 74}, {67, 1411, 87}, {39, 1151, 48}});
    for (auto c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.canEat(vector<int>() = {16, 38, 8, 41, 30, 31, 14, 45, 3, 2, 24, 23, 38, 30, 31, 17, 35, 4, 9, 42, 28, 18, 37, 18, 14, 46, 11, 13, 19, 3, 5, 39, 24, 48, 20, 29, 4, 19, 36, 11, 28, 49, 38, 16, 23, 24, 4, 22, 29, 35, 45, 38, 37, 40, 2, 37, 8, 41, 33, 8, 40, 27, 13, 4, 33, 5, 8, 14, 19, 35, 31, 8, 8}, vector<vector<int>>() = {{43, 1054, 49}, {48, 690, 92}, {28, 1201, 56}, {47, 948, 43}, {57, 233, 25}, {32, 1293, 65}, {0, 1646, 34}, {43, 1467, 39}, {39, 484, 23}, {21, 1576, 69}, {12, 1222, 68}, {9, 457, 83}, {32, 65, 9}, {10, 1424, 42}, {35, 534, 3}, {23, 83, 22}, {33, 501, 33}, {25, 679, 51}, {2, 321, 42}, {1, 240, 68}, {7, 1297, 42}, {45, 480, 72}, {26, 1472, 9}, {6, 649, 90}, {26, 361, 57}, {49, 1592, 7}, {11, 158, 95}, {35, 448, 24}, {41, 1654, 10}, {61, 510, 43}, {31, 1230, 95}, {11, 1471, 12}, {37, 43, 84}, {56, 1147, 48}, {69, 1368, 65}, {22, 170, 24}, {56, 192, 80}, {34, 1207, 69}, {1, 1226, 22}, {37, 1633, 50}, {11, 98, 58}, {17, 125, 13}, {0, 1490, 5}, {37, 1732, 43}, {45, 793, 14}, {16, 578, 72}, {50, 241, 78}});
    for (auto c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.canEat(vector<int>() = {5, 2, 6, 4, 1}, vector<vector<int>>() = {{3, 1, 2}, {4, 10, 3}, {3, 10, 100}, {4, 100, 30}, {1, 3, 1}});
    for (auto c : r)
        cout << c << ", ";
    cout << endl;

    r = sol.canEat(vector<int>() = {7, 4, 5, 3, 8}, vector<vector<int>>() = {{0, 2, 2}, {4, 2, 4}, {2, 13, 10000000}});
    for (auto c : r)
        cout << c << ", ";
    cout << endl;
}