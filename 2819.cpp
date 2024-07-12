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
    vector<long long> minimumRelativeLosses(vector<int> &p, vector<vector<int>> &queries)
    {
        sort(begin(p), end(p));

        int n = p.size();
        vector<long long> sum(n);
        for (auto i = 0; i < n; ++i)
            sum[i] = (i ? sum[i - 1] : 0) + p[i];

        vector<long long> rv;
        for (auto &q : queries)
        {
            auto k = q[0];
            auto m = q[1];

            int lo = n - m;
            int hi = n - 1;

            while (lo <= hi)
            {
                int md = (lo + hi) / 2;
                auto lt = m - n + md;
                if (p[md] >= k && 2 * k - p[md] <= p[lo])
                    hi = md - 1;
                else
                    lo = md + 1;
            }

            long long b = (n - lo) * k;
            long long a = sum[n - 1] - sum[lo - 1] - b;
            b += sum[m - n + lo - 1];
            rv.push_back(b - a);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<long long> r;

    r = sol.minimumRelativeLosses(vector<int>() = {1, 9, 22, 10, 19}, vector<vector<int>>() = {{18, 4}, {5, 2}});
    for (auto rr : r)
        cout << rr << ", ";
    cout << endl;
}