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
        array<int, 26> cnt = {};
        for (auto t : tasks) {
            ++cnt[t - 'A'];
        }

        priority_queue<int> pq;
        for (auto i = 0; i < 26; ++i) {
            if (cnt[i])
                pq.push(cnt[i]);
        }

        int rv = 0;
        while (pq.size()) {
            queue<int> q;
            int r = 0;
            for (auto i = 0; i < n + 1 && pq.size(); ++i) {
                auto v = pq.top();
                pq.pop();
                if (--v > 0) {
                    q.push(v);
                }
                ++r;
            }

            if (q.size() || pq.size())
                rv += n + 1;
            else
                return rv + r;

            while (q.size())
                pq.push(q.front()), q.pop();
        }
        return -1;
    }
};

int main() {
    Solution sol;
    int r;

    r = sol.leastInterval(vector<char>() = {'A', 'A', 'B', 'B', 'C', 'D'}, 1);
    cout << r << endl;

    r = sol.leastInterval(vector<char>() = {'A', 'A', 'A', 'B', 'B', 'B', 'C',
                                            'C', 'C', 'D', 'D', 'E'},
                          3);
    cout << r << endl;

    r = sol.leastInterval(vector<char>() = {'A', 'A', 'A', 'B', 'C'}, 3);
    cout << r << endl;

    r = sol.leastInterval(vector<char>() = {'X', 'X', 'Y', 'Y'}, 2);
    cout << r << endl;
}
