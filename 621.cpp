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
    int leastInterval(vector<char>& tasks, int n) {
        array<int, 26> freq = {};
        int max_count = 0;

        for (auto& t : tasks) {
            max_count = max(max_count, ++freq[t - 'A']);
        }

        int ticks = (max_count - 1) * (n + 1);
        for (auto f : freq) {
            if (f == max_count)
                ++ticks;
        }
        return ticks;
        // return max((int)tasks.size(), ticks);
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.leastInterval(vector<char>() = {'A', 'B', 'C'}, 2);
    cout << r << endl;

    r = sol.leastInterval(vector<char>() = {'A', 'A', 'A', 'B', 'B', 'B'}, 3);
    cout << r << endl;
}
