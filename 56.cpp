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
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        map<int, int> points;
        for (auto& interval : intervals) {
            auto l = interval[0], r = interval[1];
            ++points[l];
            --points[r];
        }

        int left = -1;
        vector<vector<int>> rv;
        for (auto& p : points) {
            if (p.second >= 0) {
                if (left == -1) {
                    left = p.first;
                }
            } else { /* p.second < 0 */
                left = -1;
                rv.push_back({left, p.first});
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}