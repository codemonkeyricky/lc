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
  public:
    vector<int> gcdValues(vector<int>& A, vector<long long>& queries) {
        /* count frequency of elements */
        unordered_map<int, int> cnt;
        for (int a : A) {
            cnt[a]++;
        }

        int m = *max_element(A.begin(), A.end());
        vector<int> gcd(m + 1);   /* maximally m unique gcds */
        for (int a = m; a > 0; --a) {
            long long mul = 0;
            for (int b = a; b <= m; b += a) {
                mul += cnt[b];
            }
            gcd[a] = mul * (mul - 1) / 2;
            for (int b = a * 2; b <= m; b += a) {
                gcd[a] -= gcd[b];
            }
        }

        partial_sum(gcd.begin(), gcd.end(), gcd.begin()); // prefix sum
        vector<int> res;
        for (int q : queries) {
            res.push_back(upper_bound(gcd.begin(), gcd.end(), q) - gcd.begin());
        }
        return res;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
