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
    long long putMarbles(vector<int> &weights, int k)
    {
        long long mmin = 0, mmax = 0, n = weights.size();
        priority_queue<array<int, 3>> q;
        for (auto i = 1; i < n; ++i)
            q.push({-weights[i - 1] - weights[i], i - 1, i});
        
        int kk = k - 1;
        mmin = weights.front() + weights.back();
        while (kk)
        {
            auto [sum, i, j] = q.top();
            mmin -= sum, --kk;
            q.pop();
        }

        q = priority_queue<array<int, 3>>();
        for (auto i = 1; i < n; ++i)
            q.push({weights[i - 1] + weights[i], i - 1, i});

        mmax = weights.front() + weights.back();
        kk = k - 1;
        while (kk)
        {
            auto [sum, i, j] = q.top();
            mmax += sum, --kk;
            q.pop();
        }

        return mmax - mmin;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.putMarbles(vector<int>() = {1, 4, 2, 5, 2}, 3);
    cout << r << endl;

    r = sol.putMarbles(vector<int>() = {1, 3, 5, 1}, 2);
    cout << r << endl;
}