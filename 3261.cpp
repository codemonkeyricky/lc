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

void pvll(vector<long long>& v) {

    for (auto& vv : v)
        cout << vv << ", ";
    cout << endl;
}

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
    vector<long long> countKConstraintSubstrings(string s, int k,
                                                 vector<vector<int>>& queries) {
        int n = s.size();
        vector<array<int, 2>> ones, zeroes;
        ones.push_back({0, -1});
        zeroes.push_back({0, -1});
        int z = 0, o = 0;

        vector<array<int, 2>> violations;
        for (auto i = 0; i < n; ++i) {
            z += s[i] == '0';
            o += s[i] == '1';

            if (s[i] == '0')
                zeroes.push_back({z, i});
            else
                ones.push_back({o, i});

            if (z - k - 1 >= 0 && o - k - 1 >= 0) {
                array<int, 2> target;

                target = {z - k - 1, 0};
                auto z_k =
                    (*lower_bound(zeroes.begin(), zeroes.end(), target))[1];

                target = {o - k - 1, 0};
                auto o_k = (*lower_bound(ones.begin(), ones.end(), target))[1];

                violations.push_back({min((int)z_k, (int)o_k), i});
            }
        }

        return {};
    }
};

int main() {
    Solution sol;
    vll r;

    r = sol.countKConstraintSubstrings("0001111", 2, vvi() = {{0, 6}});
    pvll(r);
}
