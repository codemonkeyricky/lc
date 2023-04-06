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
    bool isPrime(int k)
    {
        k -= '0';
        return k == 2 || k == 3 || k == 5 || k == 7;
    }

public:
    int beautifulPartitions(string s, int k, int minl)
    {
        int n = s.size();
        vector<vector<long long>> dp(k + 1, vector<long long>(n));
        int MOD = 1000000007;

        // base case
        for (auto i = 0; i < n; ++i)
            dp[1][i] = isPrime(s[0]) && !isPrime(s[i]);

#if 1
        for (auto i = 2; i <= k; ++i)
            for (auto j = (i * minl) - 1; j < n; ++j)
                if (!isPrime(s[j]))
                    for (int start = ((i - 1) * minl) - 1; start <= (j - minl); ++start)
                        if (isPrime(s[start + 1]))
                            dp[i][j] = (dp[i][j] + dp[i - 1][start]) % 1000000007;
#else
        vector<long long> prevRow(n);
        for (int i = 0; i + 1 < n; ++i)
        {
            if (isPrime(s[i + 1]))
                prevRow[i] = dp[i][1]; // update IFF next_index is prime and capable of starting a substring
            if (i - 1 >= 0)
                prevRow[i] = (prevRow[i] + prevRow[i - 1]) % MOD;
        }

        for (auto kk = 2; kk <= k; ++kk)
        {
            vector<long long> currRow(n);
            for (auto end = (kk * minl) - 1; end < n; ++end)
                if (!isPrime(s[end]))
                {
                    long long prefixSum = prevRow[end - minl];
                    int start = ((kk - 1) * minl) - 1;
                    if (start - 1 >= 0)
                        prefixSum = (prefixSum - prevRow[start - 1] + MOD) % MOD;

                    dp[end][kk] = (dp[end][kk] + prefixSum) % MOD;

                    // update current_row's column only if the next_index is a prime and capable of starting a substring
                    if (end + 1 < n && isPrime(s[end + 1]))
                        currRow[end] = (currRow[end] + dp[end][kk]) % MOD;
                }

            // re-calclate prefix sum of current row dp values for each column
            for (int c = 1; c <= n - 1; ++c)
                currRow[c] = (currRow[c] + currRow[c - 1]) % MOD;

            // swap previous_row dp values and current_row dp values. why ?
            // Because current row will become previous row for next row
            swap(prevRow, currRow);
        }
#endif

        return dp[k][n-1];
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.beautifulPartitions("23542185131", 3, 2);
    cout << r << endl;
}