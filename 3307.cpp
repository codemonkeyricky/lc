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
    char kthCharacter(long long k, vector<int>& ops) {

        if (ops.size() > 47)
            ops.resize(47);

        --k;
        vector<array<long long, 2>> p;
        p.push_back({k, 1ll << ops.size()});

        while (p.back()[1] != 1) {
            auto b = p.back();
            p.push_back({b[0] % (b[1] / 2), b[1] / 2});
        }

        reverse(p.begin(), p.end());

        assert(p.size() == ops.size() + 1);

        char rv = 'a';
        for (auto i = 0; i < ops.size(); ++i) {
            if (ops[i] && p[i + 1][0] > p[i][0])
                rv = (rv == 'z') ? 'a' : rv + 1;
        }

        return rv;
    }
};

int main() {
    Solution sol;
    char r;

    r = sol.kthCharacter(5, vector<int>() = {0, 0, 0});
    cout << r << endl;

    r = sol.kthCharacter(10, vector<int>() = {0, 1, 0, 1});
    cout << r << endl;
}
