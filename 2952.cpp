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
    int minimumAddedCoins(vector<int> &c, int target)
    {
        int res = 0, obtain = 0;
        sort(begin(c), end(c));
        for (int i = 0; i < c.size() && obtain < target; ++i)
        {
            while (obtain + 1 < c[i])
            {
                obtain += obtain + 1;
                ++res;
            }
            obtain += c[i];
        }
        while (obtain < target)
        {
            obtain += obtain + 1;
            ++res;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumAddedCoins(vector<int>() = {1, 1, 1}, 20);
    cout << r << endl;

    r = sol.minimumAddedCoins(vector<int>() = {1, 1, 1}, 20);
    cout << r << endl;

    r = sol.minimumAddedCoins(vector<int>() = {1, 4, 10, 5, 7, 19}, 19);
    cout << r << endl;

    r = sol.minimumAddedCoins(vector<int>() = {1, 4, 10}, 19);
    cout << r << endl;
}
