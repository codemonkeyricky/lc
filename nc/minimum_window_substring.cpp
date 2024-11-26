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
    bool contains(unordered_map<char, int>& bigger,
                  unordered_map<char, int>& smaller) {

        for (auto& small : smaller) {
            if (bigger[small.first] < small.second)
                return false;
        }

        return true;
    }

  public:
    string minWindow(string s, string t) {
        unordered_map<char, int> cnt;
        for (auto i = 0; i < t.size(); ++i) {
            ++cnt[t[i]];
        }

        array<int, 2> rv = {0, (int)1e9};
        unordered_map<char, int> curr;
        for (auto i = 0, j = 0; j <= s.size(); ++j) {
            if (j < s.size())
                ++curr[s[j]];
            while (contains(curr, cnt)) {
                if (j - i < rv[1] - rv[0]) {
                    rv = {i, j};
                }
                --curr[s[i++]];
            }
        }
        if (rv[1] == 1e9)
            return "";
        else {
            return s.substr(rv[0], rv[1] - rv[0] + 1);
        }
    }
};

int main() {
    Solution sol;
    string r;

    r = sol.minWindow("ADOBECODEBANC", "ABC");
    cout << r << endl;
}
