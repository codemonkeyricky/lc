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
    int minimumTime(vector<int> &A, vector<int> &B, int x)
    {
        int n = A.size();
        int sa = accumulate(A.begin(), A.end(), 0);
        int sb = accumulate(B.begin(), B.end(), 0);
        vector<array<int, 2>> BA;
        for (auto i = 0; i < n; ++i)
            BA.push_back({B[i], A[i]});
        sort(begin(BA), end(BA));
        vector<int> dp(n + 1);
        for (auto j = 0; j < n; ++j)
            for (auto i = j + 1; i > 0; --i)
                dp[i] = max(dp[i], dp[i - 1] + i * BA[j][0] + BA[j][1]);
        for (int i = 0; i <= n; ++i)
            if (sb * i + sa - dp[i] <= x)
                return i;
        return -1;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumTime(vector<int>() = {99, 1, 1}, vector<int>() = {3, 2, 1}, 100);
    cout << r << endl;
}