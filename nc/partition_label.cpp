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
    vector<int> partitionLabels(string s) {
        vector<int> letters(26, -1);
        int n = s.size();
        for (auto i = 0; i < n; ++i) {
            auto k = s[i] - 'a';
            letters[k] = i;
        }

        vector<int> rv;
        for (auto i = 0, l = 0, r = letters[s[i] - 'a']; i <= n; ++i) {
            if (i > r) {
                rv.push_back({r - l + 1});
                if (i < n) {
                    /* reset */
                    int k = s[i] - 'a';
                    l = i;
                    r = letters[k];
                }
            } else {
                /* extend r */
                r = max(r, letters[s[i] - 'a']);
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    vi r;

    r = sol.partitionLabels("xyxxyzbzbbisl");
    pvi(r);
}
