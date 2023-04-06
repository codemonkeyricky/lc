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
    long long makeSubKSumEqual(vector<int> &arr, int k)
    {
        long long sz = arr.size(), res = 0;
        for (int i = 0; i < k; ++i)
        {
            vector<int> cycle;
            for (int j = i; arr[j] != 0; j = (j + k) % sz)
            {
                cycle.push_back(arr[j]);
                arr[j] = 0;
            }
            nth_element(begin(cycle), begin(cycle) + cycle.size() / 2, end(cycle));
            for (int n : cycle)
                res += abs(n - cycle[cycle.size() / 2]);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.makeSubKSumEqual(vector<int>() = {10, 3, 8}, 2);
    cout << r << endl;

    r = sol.makeSubKSumEqual(vector<int>() = {2, 5, 5, 7}, 3);
    cout << r << endl;

    r = sol.makeSubKSumEqual(vector<int>() = {1, 4, 1, 3}, 2);
    cout << r << endl;
}