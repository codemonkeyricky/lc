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
    void update(int k, int v)
    {
        ++k;
        for (; k < 100001; k += k & -k)
            bit[k] += v;
    }

    int get(int k, int rv = 0)
    {
        ++k;
        for (; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

    vector<int> bit;
    static constexpr int N = 100001;

public:
    long long countOperationsToEmptyArray(vector<int> &nums)
    {
        bit = vector<int>(N + 1);
        int n = nums.size();
        priority_queue<int> q;
        unordered_map<int, int> lookup;
        for (int i = 0; i < n; ++i)
            lookup[nums[i]] = i, q.push(-nums[i]), update(i, 1);

        int pos = 0;
        long long rv = 0;
        while (q.size())
        {
            int n = -q.top();
            q.pop();

            int k = lookup[n];
            int m = get(pos - 1);
            int l = 0, r = 0;
            if (k >= pos)
                r = get(k - 1);
            else
                r = get(N - 1), l = get(k - 1);
            rv += r - m + l + 1;
            update(k, -1);
            pos = lookup[n];
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countOperationsToEmptyArray(vector<int>() = {1, 2, 3});
    cout << r << endl;

    r = sol.countOperationsToEmptyArray(vector<int>() = {1, 2, 4, 3});
    cout << r << endl;

    r = sol.countOperationsToEmptyArray(vector<int>() = {3, 4, -1});
    cout << r << endl;
}