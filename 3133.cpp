#include <algorithm>
#include <array>
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
    long long minEnd(long long n, long long x) {
        long long nn = n - 1;
        unsigned long long mask = -1;

        long long rv = x;
        int src = 0;
        for (auto dst = 0; dst < 64; ++dst) {
            if ((1ll << dst) & x) {
                ;
            } else {
                if ((1ll << src++) & nn)
                    rv |= 1ll << dst;
                else
                    ;
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minEnd(3, 4);
    cout << r << endl;
}
