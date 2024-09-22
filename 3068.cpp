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

    array<long long, 2> dfs(vector<set<int>>& al, vector<int>& nums, int k,
                            int u, int p) {

        priority_queue<array<long long, 2>> nq, nnq;

        // two broad cases
        //  1. u not_xor
        //      can have even number of v xor's
        //  2. u is xor
        //      can have odd number of v xor's

        long long n_sum = 0;
        map<int, long long> n_map;
        for (auto& v : al[u]) {
            if (v != p) {
                auto [n, nn] = dfs(al, nums, k, v, u);
                n_sum += n;
                n_map[v] = n;
                nnq.push({nn, v});
            }
        }
        array<long long, 2> rv = {nums[u], nums[u] ^ k};
        array<long long, 2> rrv = {n_sum, 0};

        bool is_root = (p == -1);
        for (auto i = 0; i < al[u].size() - !is_root; ++i) {

            // Replace one not flipped with highest xor
            auto [value, vertex] = nnq.top();
            nnq.pop();
            n_sum -= n_map[vertex];
            n_sum += value;

            rrv[(i + 1) % 2] = max(rrv[(i + 1) % 2], n_sum);
        }

        return {rv[0] + rrv[0], rv[1] + rrv[1]};
    }

  public:
    long long maximumValueSum(vector<int>& nums, int k,
                              vector<vector<int>>& edges) {
        int n = nums.size();
        vector<set<int>> al(n);

        for (auto& e : edges) {
            auto a = e[0], b = e[1];
            al[a].insert(b), al[b].insert(a);
        }

        auto rv = dfs(al, nums, k, 0, -1);
        return max({rv[0], rv[1]});
    }
};

int main() {
    Solution sol;
    long long r;

    r = sol.maximumValueSum(
        vector<int>() = {7, 7, 7, 7, 7, 7}, 3,
        vector<vector<int>>() = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}});
    cout << r << endl;

    r = sol.maximumValueSum(vector<int>() = {2, 3}, 7,
                            vector<vector<int>>() = {{0, 1}});
    cout << r << endl;

    r = sol.maximumValueSum(vector<int>() = {1, 2, 1}, 3,
                            vector<vector<int>>() = {{0, 1}, {0, 2}});
    cout << r << endl;
}
