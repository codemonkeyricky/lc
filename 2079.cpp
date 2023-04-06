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
    int wateringPlants(vector<int> &plants, int capacity)
    {
        int rv = 0;
        int cap = capacity;
        for (auto i = 0; i < plants.size(); ++i, ++rv)
        {
            if (cap < plants[i])
                rv += i * 2, cap = capacity;
            cap -= plants[i];
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.wateringPlants(vector<int>() = {2, 2, 3, 3}, 5);
    cout << r << endl;
}