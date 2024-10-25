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
    int eval(string& s, int i, int j, vector<int>& lookup) {
        int sum = 0, op = 1, interm = 0; // 1 to add, -1 to subtract
        for (auto k = i; k <= j; ++k) {
            if (k == j || s[k] == '+' || s[k] == '-') {
                /* evaluate */
                sum += interm * op;
                interm = 0;
                if (k < j)
                    op = s[k] == '+' ? 1 : -1;
            } else if (s[k] == '(') {
                interm = eval(s, k + 1, lookup[k], lookup);
                k = lookup[k];
                sum += interm * op;
                interm = 0;
            } else {
                interm *= 10;
                interm += s[k] - '0';
            }
        }
        return sum;
    }

  public:
    int calculate(string s) {

        /* remove all spaces */

        int w = 0;
        for (auto r = 0; r < s.size(); ++r) {
            if (s[r] != ' ')
                s[w++] = s[r];
        }
        s.resize(w);

        /* find all the bracket pairing */

        int n = s.size();
        vector<int> lookup(n);
        vector<int> stack;
        for (auto j = 0; j < n; ++j) {
            if (s[j] == '(') {
                stack.push_back(j);
            } else if (s[j] == ')') {
                auto i = stack.back();
                stack.pop_back();
                lookup[i] = j;
            }
        }

        /* recursively evaluate */

        return eval(s, 0, s.size(), lookup);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.calculate("1 + 1");
    cout << r << endl;

    r = sol.calculate("(1+(4+5+2)-3)+(6+8)");
    cout << r << endl;

    r = sol.calculate("2-1+2");
    cout << r << endl;
}
