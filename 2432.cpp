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
    int hardestWorker(int n, vector<vector<int>>& logs) {
        int rv = 0, ll = 0;
        for (auto i = 0; i < logs.size(); ++i)
        {
            int duration = logs[i][1] - (i ? logs[i - 1][1] : 0);
            if (duration > ll)
                ll = duration, rv = logs[i][0];
            else if (duration == ll && logs[i][0] < rv)
                rv = logs[i][0];
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}