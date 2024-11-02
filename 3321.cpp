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

using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<long long>;
using vvll = vector<vector<long long>>;

class Solution {

    void mm_remove(array<long long, 2>& m) {

        if (*it <= m) {

            /* erase something from x - perform maintenence */

            /* remove m from sum */
            sum -= m[0] * m[1];
            if (it != cn.begin()) {
                --it;
                /* include prev(it) into sum */
                sum += (*it)[0] * (*it)[1];
            } else {
                /* everything is removed */
                if (it_size >= 0) {
                    ++it;
                    --it_size;
                }
            }
        }

        /* erase element */
        cn.erase(m);
    }

    void mm_insert(array<long long, 2>& m) {

        auto new_it = cn.insert(m);

        if (it_size < _x) {
            /* it_size too small - include this in sum */
            sum += (*new_it)[0] * (*new_it)[1];
            ++it_size;

            /* all elements are in x */
            it = cn.begin();
        } else if (*it < *new_it) {

            /* *new_it is "better" - replace it */
            sum -= (*it)[0] * (*it)[1];
            sum += (*new_it)[0] * (*new_it)[1];
            /* increment it to maintain window size */
            ++it;
        }
    }

    unordered_map<long long, long long> nc;
    multiset<array<long long, 2>> cn;
    multiset<array<long long, 2>>::iterator it;
    int it_size = 0;
    int _x;
    long long sum = 0;

  public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {

        int n = nums.size();
        _x = x;

        vector<long long> rv;

        for (auto i = 0, j = 0; j < n; ++j) {

            /* insert new element into window */

            array<long long, 2> to_update = {1, nums[j]};
            if (nc.count(nums[j])) {
                to_update = {nc[nums[j]], nums[j]};
                mm_remove(to_update);
                ++to_update[0];
            }
            mm_insert(to_update);
            ++nc[nums[j]];

            if (j >= k) {
                /* remove old element from window */

                array<long long, 2> to_update = {nc[nums[i]], nums[i]};
                mm_remove(to_update);
                if (--to_update[0] > 0) {
                    mm_insert(to_update);
                }

                if (--nc[nums[i]] == 0) {
                    nc.erase(nums[i]);
                }
                ++i;
            }

            if (j >= k - 1) {
                rv.push_back(sum);
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    vector<long long> r;

    r = sol.findXSum(vector<int>() = {2, 3, 3, 4, 5, 6, 5, 4, 6, 3, 5, 5}, 6,
                     6);
    pvll(r);

    r = sol.findXSum(vector<int>() = {1, 1, 2, 2, 3, 4, 2, 3}, 6, 2);
    pvll(r);
}
