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

    int dfs(vector<int>& cnt, int i, int k, vector<long long>& suffix) {
        int n = cnt.size();

        if (k <= 0) {
            return i >= n ? 1 : suffix[i];
        }

        if (i >= cnt.size())
            return 0;

        int rv = 0;
        for (auto j = 1; j <= cnt[i]; ++j) {
            rv = (rv + dfs(cnt, i + 1, k - j, suffix)) % MOD;
        }
        return rv;
    }

  public:
    int possibleStringCount(string word, int k) {
        vector<int> cnt;

        for (auto i = 1, c = 1; i <= word.size(); ++i) {
            if (i < word.size() && word[i - 1] == word[i]) {
                ++c;
            } else {
                cnt.push_back(c);
                c = 1;
            }
        }

        vector<long long> suffix(cnt.size());
        long long m = 1;
        for (int i = cnt.size() - 1; i >= 0; --i) {
            m = (m * cnt[i]) % MOD;
            suffix[i] = m;
        }

        return dfs(cnt, 0, k, suffix);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.possibleStringCount("aaabbb", 3);
    cout << r << endl;

    r = sol.possibleStringCount("aabbccdd", 8);
    cout << r << endl;

    r = sol.possibleStringCount("aabbccdd", 7);
    cout << r << endl;
}
