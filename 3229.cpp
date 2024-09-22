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
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> normal(n);
        for (auto i = 0; i < n; ++i)
            normal[i] = target[i] - nums[i];

        set<int> set;
        priority_queue<array<int, 2>> q;
        q.push({abs(normal[0]), 0});
        set.insert(0);
        long long rv = 0;
        for (auto i = 1; i <= n; ++i) {
            if (i == n || normal[i - 1] * normal[i] <= 0) {
                while (q.size()) {
                    auto& [height, index] = q.top();

                    auto c = set.find(index);
                    int p = -1, n = -1;
                    if (c != set.begin())
                        p = *prev(c);
                    if (next(c) != set.end())
                        n = *next(c);

                    int candidate = abs(normal[*c]);
                    if (p != -1)
                        candidate =
                            min(candidate, abs(normal[*c]) - abs(normal[p]));
                    if (n != -1)
                        candidate =
                            min(candidate, abs(normal[*c]) - abs(normal[n]));

                    rv += candidate;

                    q.pop();
                    set.erase(c);
                }
            }

            if (i < n && normal[i]) {
                q.push({abs(normal[i]), i});
                set.insert(i);
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.minimumOperations(vector<int>() = {0, 0, 0, 0},
                              vector<int>() = {1, 2, 4, 3});
    cout << r << endl;

    r = sol.minimumOperations(vector<int>() = {9, 2, 6, 10, 4, 8, 3, 4, 2, 3},
                              vector<int>() = {9, 5, 5, 1, 7, 9, 8, 7, 6, 5});
    cout << r << endl;

    r = sol.minimumOperations(vector<int>() = {1, 1, 3, 4},
                              vector<int>() = {4, 1, 3, 2});
    cout << r << endl;

    r = sol.minimumOperations(vector<int>() = {1, 3, 2},
                              vector<int>() = {2, 1, 4});
    cout << r << endl;

    r = sol.minimumOperations(vector<int>() = {3, 5, 1, 2},
                              vector<int>() = {4, 6, 2, 4});
    cout << r << endl;
}