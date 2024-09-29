#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <map>
#include <iostream>
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
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> map;

        for (auto n : nums1) {
            for (int i = 1; i * i <= n; i++) {
                if (i * i == n) {
                    ++map[i];
                } else if (n % i == 0) {
                    ++map[i];
                    ++map[n / i];
                }
            }
        }

        long long int rv = 0;

        for (auto n : nums2) {
            n *= k;
            rv += map[n];
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.numberOfPairs(vector<int>() = {1, 2, 4, 12}, vector<int>() = {2, 4},
                          3);
    cout << r << endl;

    r = sol.numberOfPairs(vector<int>() = {1, 3, 4}, vector<int>() = {1, 3, 4},
                          1);
    cout << r << endl;
}
