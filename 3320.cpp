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
using ll = long long;

class Solution {

    /*
     * dp[[k][score]
     * number of ways for bob to win for a given score at k
     */

    int dfs(string& s, int k, char p, int score) {
        int n = s.size();

        if (k < 0)
            return score > 0; /// TODO???

        /*
         * F > E
         * W > F
         * E > W
         */

        ll rv = 0;
        switch (s[k]) {
        case 'F': {
            /* Bob uses F
             * Same - pass score along
             */

            /*
             * Bob uses W
             * Bob wins - can also account for lowered score
             */

            /*
             * Bob loses with E
             * Bob need to increase score
             */

            if (p != 'F')
                rv += dfs(s, k - 1, 'F', score);
            if (p != 'W')
                rv += dfs(s, k - 1, 'W', score - 1);
            if (p != 'E')
                rv += dfs(s, k - 1, 'E', score + 1);

        } break;
        case 'W': {

            /*
             * F > E
             * W > F
             * E > W
             */

            if (p != 'F') // loses
                rv += dfs(s, k - 1, 'F', score + 1);
            if (p != 'W') // same
                rv += dfs(s, k - 1, 'W', score);
            if (p != 'E') // wins
                rv += dfs(s, k - 1, 'E', score - 1);
        } break;
        case 'E': {
            if (p != 'F') // wins
                rv += dfs(s, k - 1, 'F', score - 1);
            if (p != 'W') // loses
                rv += dfs(s, k - 1, 'W', score + 1);
            if (p != 'E') // same
                rv += dfs(s, k - 1, 'E', score);
        } break;
        }

        return rv;
    }

  public:
    int countWinningSequences(string s) {
        int n = s.size();
        int rv = 0;
        for (auto score = 1; score <= n; ++score)
            rv += dfs(s, n - 1, -1, score);
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.countWinningSequences("FFF");
    cout << r << endl;
}
