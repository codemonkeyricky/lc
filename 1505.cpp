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
    const static int N = 30001;
    vector<int> bit;
    void update(int k, int v) {
        ++k;
        for (; k < N; k += k & -k)
            bit[k] += v;
    }

    int get(int k) {
        ++k;
        int rv = 0;
        for (; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

  public:
    string minInteger(string num, int k) {
        int n = num.size();

        /* use fenwick tree to record index of all numbers. As we process
         * individual, we can remove them from the tree to reduce number of
         * swaps in future iterations */

        /* all elements are present */
        bit = vector<int>(N);
        for (auto i = 0; i < n; ++i)
            update(i, 1);

        /* track digit position index by digit value */
        vector<vector<int>> arr(10);
        for (auto i = 0; i < n; ++i)
            arr[num[i] - '0'].push_back(i);

        /* track current index of each digit as they are being used up */
        vector<int> index(10);
        string rv;
        int retry;
        do {
            retry = false;

            /* prioritize small number starting with 0 */
            for (auto i = 0; i < 10 && !retry; ++i)
                /* make sure there's still more digit 'i' */
                if (index[i] < arr[i].size()) {
                    /* how many swaps are required? */
                    int count = get(arr[i][index[i]] - 1);
                    if (count <= k) {
                        /* reduce number of swaps */
                        k -= count;
                        rv += i + '0';
                        retry = true;
                        /* remove digit - it's moved to the front */
                        update(arr[i][index[i]++], -1);
                    }
                }
        } while (retry);
        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    cout << r << endl;
}
