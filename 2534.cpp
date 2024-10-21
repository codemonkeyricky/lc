#include <algorithm>
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
  public:
    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        int n = arrival.size();

        int time = 0;
        int s = -1;

        vector<vector<int>> entering(1e5 + 1), exiting(1e5 + 1);

        for (auto i = 0; i < n; ++i) {
            if (state[i]) {
                exiting[arrival[i]].push_back(i);
            } else {
                entering[arrival[i]].push_back(i);
            }
        }

#define EXIT 1
#define ENTER 0

#define N (1e5 + 1)

        vector<int> rv(n);
        for (auto i = 0, j = 0, tick = -1, door = -1;
             i < 1e5 + 1 || j < 1e5 + 1;) {

            /* i for entering, j for exiting */

            if (i > tick && j > tick) {
                /* door was unused */
                door = -1, tick = min(i, j);
            } else if (i > tick) {
                door = EXIT;
            } else {
                door = ENTER;
            }

            if (door == -1 || door == EXIT) {

                while (j < N && j <= tick) {
                    for (auto& p : exiting[j]) {
                        rv[p] = tick++;
                        door = EXIT;
                    }
                    ++j;
                }

                while (i < N && i <= tick) {
                    for (auto& p : entering[i]) {
                        rv[p] = tick++;
                        door = ENTER;
                    }
                    ++i;
                }

            } else {

                while (i < N && i <= tick) {
                    for (auto& p : entering[i]) {
                        rv[p] = tick++;
                        door = ENTER;
                    }
                    ++i;
                }

                while (j < N && j <= tick) {
                    for (auto& p : exiting[j]) {
                        rv[p] = tick++;
                        door = EXIT;
                    }
                    ++j;
                }
            }
        }
        return rv;
    }
};

int main() {
    Solution sol;
    vector<int> r;

    // {
    //     r = sol.timeTaken(vector<int>() = {0, 0, 1, 2, 8, 10, 10, 10, 10,
    //     10},
    //                       vector<int>() = {0, 1, 0, 1, 1, 0, 0, 0, 1, 1});
    //     for (auto& c : r)
    //         cout << c << ", ";
    //     cout << endl;
    // }

    // {
    //     r = sol.timeTaken(vector<int>() = {3, 3, 4, 5, 5, 5},
    //                       vector<int>() = {1, 0, 1, 0, 1, 0});
    //     for (auto& c : r)
    //         cout << c << ", ";
    //     cout << endl;
    // }

    // {
    //     r = sol.timeTaken(vector<int>() = {0, 0, 10, 11, 11, 11, 11, 11, 12,
    //     12,
    //                                        13, 14, 14, 15, 16, 18, 19, 19,
    //                                        19},
    //                       vector<int>() = {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1,
    //                       1,
    //                                        0, 0, 1, 1, 1, 1, 0});
    //     for (auto& c : r)
    //         cout << c << ", ";
    //     cout << endl;
    // }

    // {
    //     r = sol.timeTaken(vector<int>() = {0, 5, 6, 6, 7, 9, 9, 9, 10, 10,
    //     10,
    //                                        10, 10, 15, 16, 17, 17, 17},
    //                       vector<int>() = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
    //                       1,
    //                                        0, 1, 1, 0, 1, 0});
    //     for (auto& c : r)
    //         cout << c << ", ";
    //     cout << endl;
    // }

    {
        r = sol.timeTaken(vector<int>() = {0, 0, 0},
                          vector<int>() = {1, 0, 1});
        for (auto& c : r)
            cout << c << ", ";
        cout << endl;
    }

    {
        r = sol.timeTaken(vector<int>() = {0, 1, 1, 2, 4},
                          vector<int>() = {0, 1, 0, 0, 1});
        for (auto& c : r)
            cout << c << ", ";
        cout << endl;
    }
}