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

    int get(vector<int>& bit, int k) {
        int rv = 0;
        for (++k; k; k -= k & -k)
            rv += bit[k];
        return rv;
    }

    void update(vector<int>& bit, int k, int v) {
        int N = bit.size();
        for (++k; k < N; k += k & -k)
            bit[k] += v;
    }

    set<array<int, 2>>::iterator find_next(set<array<int, 2>>& s,
                                           set<array<int, 2>>::iterator& it) {
        if (next(it) == s.end())
            return s.begin();
        return ++it;
    }

    set<array<int, 2>>::iterator find_prev(set<array<int, 2>>& s,
                                           set<array<int, 2>>::iterator& it) {
        if (it == s.begin())
            return prev(s.end());
        return --it;
    }

  public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors,
                                          vector<vector<int>>& queries) {
        vector<int> sum, cnt;
        int n = colors.size();
        sum = cnt = vector<int>(n * 2 + 1);

        set<array<int, 2>> streaks;

        int streak = 1;

        int s;
        for (s = 1; s < n * 2; ++s) {
            if (colors[(s - 1) % n] == colors[s % n]) {
                break;
            }
        }

        if (s == n * 2) {
            // entire thing is alternating
            update(cnt, n, 1);
            update(sum, n, n);
            streaks.insert({0, n});
        } else {
            int ss = s, i;
            for (i = s; i != (ss + n - 1) % n; i = (i + 1) % n) {
                if (colors[(i + n - 1) % n] != colors[i % n]) {
                    ++streak;
                } else {
                    update(cnt, streak, 1);
                    update(sum, streak, streak);
                    // actually terminates at the previous color
                    // tracks start + len
                    streaks.insert({(i + n - streak) % n, streak});
                    // starts another streak from current
                    streak = 1;
                }
            }

            // final
            update(cnt, streak, 1);
            update(sum, streak, streak);
            // actually terminates at the previous color
            // tracks start + len
            streaks.insert({(i + n - streak) % n, streak});
        }

        vector<int> rv;
        for (auto& q : queries) {
            if (q[0] == 1) {
                int s = get(sum, 2 * n);
                if (q[1])
                    s -= get(sum, q[1] - 1);

                int c = get(cnt, 2 * n);
                if (q[1])
                    c -= get(cnt, q[1] - 1);

                rv.push_back(s - q[1] * c + c);
            } else { // q[0] == 2
                auto index = q[1];
                auto color = q[2];

                array<int, 2> target = {index, 0};
                auto nn = upper_bound(begin(streaks), end(streaks), target);
                auto c = nn;
                if (nn == streaks.begin()) {
                    c = prev(streaks.end());
                } else {
                    c = prev(nn);
                }

                if ((*c)[1] == 1) {
                    // glue before and after

                    auto pp = find_prev(streaks, c);
                    auto nn = find_next(streaks, c);

                    // remove c
                    update(cnt, 1, -1);
                    update(sum, 1, -1);
                    streaks.erase(c);

                    // remove after
                    auto l = (*nn)[1] - (*nn)[0];
                    update(cnt, l, 1);
                    update(sum, l, l);

                    // remove before
                    if (pp != nn) {
                        auto l = (*pp)[1] - (*pp)[0];
                        update(cnt, l, 1);
                        update(sum, l, l);
                    }

                    if (pp == nn) {
                        // insert one
                        update(cnt, n, 1);
                        update(sum, n, n);
                        streaks.insert({0, n});
                    } else {

                        int l = (*nn)[1] + (*pp)[1];
                        int s = ((*pp)[0] + n) % n;

                        update(cnt, l, 1);
                        update(sum, l, l);
                        streaks.insert({s, l});
                    }

                    streaks.erase(pp);
                    streaks.erase(nn);

                } else {
                    // larger than 1

                    if ((*c)[0] == index) {
                        // TODO: update current and merge with prev
                        // } else if (((*c)[0] + n + (*c)[1]) % n == index) {
                        //     // TODO: update current and merge with next
                        // }
                    }

                    // auto r = *it;
                    // streaks.erase(it);
                    // int l = (*it)[1] - (*it)[0];
                    // update(cnt, l, -1);
                    // update(sum, l, -l);

                    // r[0] = index;
                    // streaks.insert(r);
                    // l = r[1] - r[0];
                    // update(cnt, l, 1);
                    // update(sum, l, l);
                }
            }
        }

        return rv;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    r = sol.numberOfAlternatingGroups(
        vector<int>() = {0, 1, 1, 0, 1},
        vector<vector<int>>() = {{2, 1, 0}, {1, 4}});
    for (auto& rr : r) {
        cout << rr << ", " << endl;
    }
}

// update(sum, 1, 1, n, 4, 4, 4);
// update(sum, 1, 1, n, 4, 4, 4);
// update(sum, 1, 1, n, 3, 3, 7);
// update(sum, 1, 1, n, 3, 3, -7);
// update(sum, 1, 1, n, 1, 1, -2);
// cout << query(sum, 1, 1, n, 1, n) << endl;
