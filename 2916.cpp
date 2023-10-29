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
#define N 10005
#define ll long long
#define MOD 1000000007

    vector<ll> a, seg, segsq, lazy; 

    // Update the segment tree and handle lazy propagation.
    void update(int node, int start, int end, int l, int r, int val)
    {
        val = 1;
        if (lazy[node] != 0)
        {
            segsq[node] += ((end - start + 1) * ((lazy[node] * lazy[node]) % MOD)) % MOD + (2 * lazy[node] * seg[node]) % MOD;
            segsq[node] %= MOD;
            seg[node] += ((end - start + 1) * lazy[node]) % MOD;
            seg[node] %= MOD;
            if (start != end)
            {
                lazy[node << 1] += lazy[node];
                lazy[node << 1 | 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (start > end || start > r || end < l)
            return;

        if (l <= start && end <= r)
        {
            segsq[node] += ((end - start + 1) * (val * val) % MOD) % MOD + (2 * val * seg[node]) % MOD;
            segsq[node] %= MOD;
            seg[node] += ((end - start + 1) * val) % MOD;
            seg[node] %= MOD;
            if (start != end)
            {
                lazy[node << 1] += val;
                lazy[node << 1 | 1] += val;
            }
            return;
        }

        ll mid = (start + end) >> 1;
        update(node << 1, start, mid, l, r, val);
        update(node << 1 | 1, mid + 1, end, l, r, val);
        seg[node] = (seg[node << 1] + seg[node << 1 | 1]) % MOD;
        segsq[node] = (segsq[node << 1] + segsq[node << 1 | 1]) % MOD;
    }

public:
    int sumCounts(vector<int> &nums)
    {
        int n = nums.size();
        a = vector<ll>(n);
        seg = segsq = lazy = vector<ll>(4 * n);

        unordered_map<int, int> last_seen;
        ll rv = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            if (!last_seen.count(nums[i]))
                update(1, 1, n, i + 1, n, 1);
            else
                update(1, 1, n, i + 1, last_seen[nums[i]] - 1, 1);

            last_seen[nums[i]] = i + 1;
            rv = (rv + segsq[1]) % MOD;
        }

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.sumCounts(vector<int>() = {1, 1});
    cout << r << endl;

    r = sol.sumCounts(vector<int>() = {1, 2});
    cout << r << endl;

    r = sol.sumCounts(vector<int>() = {1, 2, 1});
    cout << r << endl;
}