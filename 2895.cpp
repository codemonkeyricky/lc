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
    int minProcessingTime(vector<int> &procs, vector<int> &tasks)
    {
        sort(begin(tasks), end(tasks), greater<int>());

        sort(begin(procs), end(procs));

        int rv = 0;
        for (auto i = 0; i < procs.size(); ++i)
            rv = max(rv, procs[i] + tasks[i * 4]);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minProcessingTime(vector<int>() = {8, 10}, vector<int>() = {2, 2, 3, 1, 8, 7, 4, 5});
    cout << r << endl;
}