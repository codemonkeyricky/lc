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
    int findRadius(vector<int> &houses, vector<int> &heaters)
    {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        vector<int> rv(houses.size(), INT_MAX);

        // For each house, calculate distance to nearest RHS heater
        for (int i = 0, h = 0; i < houses.size() && h < heaters.size();)
        {
            if (houses[i] <= heaters[h])
            {
                rv[i] = heaters[h] - houses[i];
                i++;
            }
            else
            {
                h++;
            }
        }

        // For each house, calculate distance to nearest LHS heater
        for (int i = houses.size() - 1, h = heaters.size() - 1; i >= 0 && h >= 0;)
        {
            if (houses[i] >= heaters[h])
            {
                rv[i] = min(rv[i], houses[i] - heaters[h]);
                i--;
            }
            else
            {
                h--;
            }
        }

        return *max_element(rv.begin(), rv.end());

        // sort(begin(houses), end(houses));
        // sort(begin(heaters), end(heaters));

        // int l = 1, r = 1e9;
        // while (l < r)
        // {
        //     auto m = (l + r) / 2;
        //     int i, j;
        //     for (i = j = 0; i < houses.size() && j < heaters.size(); ++j)
        //         while (i < houses.size() && abs(heaters[j] - houses[i]) <= m)
        //             ++i;
        //     if (i >= houses.size())
        //         r = m;
        //     else
        //         l = m + 1;
        // }
        // return l;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.findRadius(vector<int>() = {1, 2, 3, 4}, vector<int>() = {1, 4});
    cout << r << endl;
}