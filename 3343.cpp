#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

TreeNode* populate(vector<int>& tree) { return recurse(tree, 0); }

void pvi(vector<int>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {

    const int MOD = 1e9 + 7;

    long long nk(long long n, long long k) {
        if (k == 0)
            return 1;
        return (n * nk(n - 1, k - 1)) / k;
    }

    vector<vector<unordered_map<int, long long>>> dp;

    long long dfs(string& num, /* num */
                  int k,       /* index at num */
                  int odd,     /* how many odd spots left */
                  int sum) {
        int n = num.size();

        if (odd < 0)
            return 0;

        if (odd > num.size() - k)
            return 0;

        if (k >= n)
            return sum == 0;

        if (!dp[k][odd].count(sum)) {

            /* find how many numbers here have the same digit */
            int j;
            for (j = k; j < num.size() && num[j] == num[k]; ++j)
                ;

            long long rv = 0, d = num[k] - '0';
            for (auto i = k; i <= j; ++i) {
                auto odds = i - k;
                auto evens = j - i;
                auto odd_spots = odd;
                auto even_spots = num.size() - k - odd;
                auto a = nk(odd_spots, odds);
                auto b = nk(even_spots, evens);
                rv = (rv +
                      a * b *
                          dfs(num, j, odd - odds, sum + (odds - evens) * d)) %
                     MOD;
            }

            dp[k][odd][sum] = rv;
        }

        return dp[k][odd][sum];
    }

  public:
    int countBalancedPermutations(string num) {

        sort(num.begin(), num.end());
        auto sum =
            accumulate(num.begin(), num.end(), 0ll,
                       [](long long sum, char c) { return sum + c - '0'; });

        if (sum % 2)
            return 0;

        dp = vector<vector<unordered_map<int, long long>>>(
            num.size(),
            vector<unordered_map<int, long long>>((num.size() + 1) / 2 + 1));

        return dfs(num, 0, (num.size() + 1) / 2, 0);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countBalancedPermutations(
        "34873486406991899612015176290787725169025811074");
    cout << r << endl;

    r = sol.countBalancedPermutations("074309063180061");
    cout << r << endl;

    r = sol.countBalancedPermutations("123");
    cout << r << endl;

    r = sol.countBalancedPermutations("112");
    cout << r << endl;
}
