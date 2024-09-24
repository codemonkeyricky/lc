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

class Solution {
  public:
    int minimumPushes(string word) {
        array<int, 26> cnt = {};
        for (auto& c : word)
            ++cnt[c - 'a'];

        sort(begin(cnt), end(cnt), greater<int>());

        int rv = 0;
        for (auto i = 0; i < 26 && cnt[i]; ++i) {
            rv += cnt[i] * ((i / 8) + 1);
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumPushes("aabbccddeeffgghhiiiiii");
    cout << r << endl;
}
