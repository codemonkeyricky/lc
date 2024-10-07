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
    int minChanges(string s) {

        int rv = 0;
        int n = s.size();
        for (auto i = 0; i < n; i += 2) {
            if (s[i] != s[i + 1])
                ++rv;
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minChanges("111111111110010001");
    cout << r << endl;

    r = sol.minChanges("0000");
    cout << r << endl;

    r = sol.minChanges("10");
    cout << r << endl;

    r = sol.minChanges("1001");
    cout << r << endl;
}
