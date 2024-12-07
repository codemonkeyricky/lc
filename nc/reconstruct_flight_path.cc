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

    bool dfs(unordered_map<string, map<string, int>>& al, string u,
             vector<string>& rv, int cnt) {

        if (cnt == 0)
            return true;

        for (auto& v : al[u]) {
            if (v.second) {
                rv.push_back(v.first);
                --v.second;
                if (dfs(al, v.first, rv, cnt - 1))
                    return true;
                --v.second;
                rv.pop_back();
            }
        }
        return false;
    }

  public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, map<string, int>> al;

        for (auto& t : tickets) {
            ++al[t[0]][t[1]];
        }

        vector<string> rv;
        rv.push_back("JFK");
        dfs(al, "JFK", rv, tickets.size());

        return rv;
    }
};

int main() {
    Solution sol;
    int r;

    sol.findItinerary(vector<vector<string>>() = {{"EZE", "AXA"},
                                                  {"TIA", "ANU"},
                                                  {"ANU", "JFK"},
                                                  {"JFK", "ANU"},
                                                  {"ANU", "EZE"},
                                                  {"TIA", "ANU"},
                                                  {"AXA", "TIA"},
                                                  {"TIA", "JFK"},
                                                  {"ANU", "TIA"},
                                                  {"JFK", "TIA"}});
}
