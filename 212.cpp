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

    struct Trie {
        array<Trie*, 26> chars = {};
        bool word = false;
    };

    Trie root;

    void dfs(vector<vector<char>>& b, Trie* t, int i, int j, string& curr,
             vector<vector<int>>& visited, unordered_set<string>& seen) {

        int k = b[i][j] - 'a';
        if (!t->chars[k]) {
            return;
        }

        t = t->chars[k];

        curr += string(1, b[i][j]);

        if (t->word) {
            seen.insert(curr);
        }

        int m = b.size();
        int n = b[0].size();

        visited[i][j] = true;

        vector<int> offset = {0, -1, 0, 1, 0};
        for (auto k = 0; k < 4; ++k) {
            auto ni = i + offset[k + 0];
            auto nj = j + offset[k + 1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                if (!visited[ni][nj]) {
                    dfs(b, t, ni, nj, curr, visited, seen);
                }
            }
        }

        visited[i][j] = false;

        curr.pop_back();
    }

  public:
    vector<string> findWords(vector<vector<char>>& b, vector<string>& w) {

        /* Create trie */

        for (auto& ww : w) {
            Trie* trie = &root;
            for (auto& c : ww) {
                int k = c - 'a';
                if (trie->chars[k] == nullptr)
                    trie->chars[k] = new Trie();
                trie = trie->chars[k];
            }
            trie->word = true;
        }

        unordered_set<string> rv;
        int m = b.size(), n = b[0].size();
        vector<vector<int>> visited(m, vector<int>(n));
        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                dfs(b, &root, i, j, string() = "", visited, rv);
            }
        }

        return vector<string>(rv.begin(), rv.end());
    }
};

int main() {
    Solution sol;
    int r;

    sol.findWords(vector<vector<char>>() = {{'a', 'a'}},
                  vector<string>() = {"aaa"});

    sol.findWords(vector<vector<char>>() = {{'o', 'a', 'a', 'n'},
                                            {'e', 't', 'a', 'e'},
                                            {'i', 'h', 'k', 'r'},
                                            {'i', 'f', 'l', 'v'}},
                  vector<string>() = {"oath", "pea", "eat", "rain"});
}
