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
    int minimumOperationsToMakeEqual(int x, int y) {

        set<int> seen;
        queue<int> q;
        q.push(x);
        int rv = 0;
        while (q.size()) {
            auto s = q.size();
            while (s) {
                auto x = q.front();
                q.pop();
                seen.insert(x);

                if (x == y)
                    return rv;

                if (!seen.count(x + 1)) {
                    q.push(x + 1);
                }

                if (!seen.count(x - 1)) {
                    q.push(x - 1);
                }

                if (x % 11 == 0 && !seen.count(x / 11)) {
                    q.push(x / 11);
                }

                if (x % 5 == 0 && !seen.count(x / 5)) {
                    q.push(x / 5);
                }

                --s;
            }
            ++rv; 
        }

        return -1; 
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumOperationsToMakeEqual(25, 30);
    cout << r << endl;
}
