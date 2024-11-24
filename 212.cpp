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

    using vi = vector<int>;
    using vvi = vector<vector<int>>;
    using vvc = vector<vector<char>>;
    using vs = vector<string>;

    struct Trie {
        array<Trie*, 26> letters = {};
        bool ending = false;
    };

    Trie root;

    void dfs(vvc& b, int i, int j, Trie* trie, string& s, vvi& seen,
             set<string>& rv) {
        int m = b.size(), n = b[0].size();

        if (trie->letters[b[i][j] - 'a'] == nullptr)
            return;

        trie = trie->letters[b[i][j] - 'a'];
        s.push_back(b[i][j]);

        if (trie->ending) {
            rv.insert(s);
        }

        vi offset = {0, -1, 0, 1, 0};
        seen[i][j] = true;
        for (auto k = 0; k < 4; ++k) {
            auto ni = i + offset[k + 0];
            auto nj = j + offset[k + 1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                if (!seen[ni][nj]) {
                    dfs(b, ni, nj, trie, s, seen, rv);
                }
            }
        }
        seen[i][j] = false;
        s.pop_back();
    }

  public:
    vector<string> findWords(vector<vector<char>>& b, vector<string>& words) {
        int m = b.size(), n = b[0].size();

        /* construct trie */
        for (auto& w : words) {
            auto c = &root;
            for (auto i = 0; i < w.size(); ++i) {
                if (c->letters[w[i] - 'a'] == nullptr)
                    c->letters[w[i] - 'a'] = new Trie();
                c = c->letters[w[i] - 'a'];
            }
            c->ending = true;
        }

        set<string> rv;
        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                auto seen = vvi(12, vi(12));
                dfs(b, i, j, &root, string() = {}, seen, rv);
            }
        }
        return vector<string>(rv.begin(), rv.end());
    }
};

int main() {
    Solution sol;
    int r;

    sol.findWords(vector<vector<char>>() =
                      {
                          {'a', 'b', 'c'},
                          {'a', 'e', 'd'},
                          {'a', 'f', 'g'},

                      },
                  vector<string>() = {"eaafgdcba"});

    sol.findWords(vector<vector<char>>() = {{'o', 'a', 'a', 'n'},
                                            {'e', 't', 'a', 'e'},
                                            {'i', 'h', 'k', 'r'},
                                            {'i', 'f', 'l', 'v'}},
                  vector<string>() = {"oath", "pea", "eat", "rain"});
}
