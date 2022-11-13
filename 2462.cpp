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
    long long totalCost(vector<int> &costs, int k, int candidates)
    {
        priority_queue<array<int, 2>> first, second;
        int i = 0, j = costs.size() - 1;
        long long rv = 0;
        while (k--)
        {
            while (first.size() < candidates && i <= j)
                first.push({-costs[i], -i}), ++i;

            while (second.size() < candidates && i <= j)
                second.push({-costs[j], -j}), --j;

            if (i > j)
                while (second.size())
                    first.push(second.top()), second.pop();

            if (second.empty() || -first.top()[0] < -second.top()[0] || (first.top()[0] == second.top()[0] && -first.top()[1] < -second.top()[1]))
            {
                rv += -first.top()[0];
                first.pop();
            }
            else 
            {
                rv += -second.top()[0];
                second.pop();
            }
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.totalCost(vector<int>() = {69, 10, 63, 24, 1, 71, 55, 46, 4, 61, 78, 21, 85, 52, 83, 77, 42, 21, 73, 2, 80, 99, 98, 89, 55, 94, 63, 50, 43, 62, 14}, 21, 31);
    cout << r << endl;

    r = sol.totalCost(vector<int>() = {1, 2, 4, 1}, 3, 3);
    cout << r << endl;

    r = sol.totalCost(vector<int>() = {17, 12, 10, 2, 7, 2, 11, 20, 8}, 3, 4);
    cout << r << endl;
}