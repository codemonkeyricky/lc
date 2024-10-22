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
    double myPow(double x, long long n) {

        if (n < 0) {
            x = 1 / x;
            n *= -1;
        }

        if (n == 0)
            return 1;

        if (n == 1) {
            return x;
        }

        double r = myPow(x, n / 2);

        return r * r * myPow(x, n % 2);
    }
};

int main() {
    Solution sol;
    double r;

    r = sol.myPow(2.1, 3);
    cout << r << endl;

    r = sol.myPow(2.1, 3);
    cout << r << endl;

    r = sol.myPow(2, 10);
    cout << r << endl;
}
