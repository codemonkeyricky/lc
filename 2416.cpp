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

struct Treen {
    int val;
    Treen* left;
    Treen* right;
    Treen() : val(0), left(nullptr), right(nullptr) {}
    Treen(int x) : val(x), left(nullptr), right(nullptr) {}
    Treen(int x, Treen* left, Treen* right)
        : val(x), left(left), right(right) {}
};

Treen* recurse(vector<int>& tree, int k) {
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new Treen(tree[k], recurse(tree, k * 2 + 1),
                        recurse(tree, k * 2 + 2));
}

Treen* populate(vector<int>& tree) { return recurse(tree, 0); }

struct Trie {
    Trie* next[26] = {};
    int cnt = 0;
};

class Solution {
    // Initialize the root n of the trie.
    Trie root;

  public:
    // Insert function for the word.
    void insert(string word) {
        auto n = &root;
        for (char c : word) {
            // If new prefix, create a new trie n.
            if (!n->next[c - 'a']) {
                n->next[c - 'a'] = new Trie();
            }
            // Increment the count of the current prefix.
            ++n->next[c - 'a']->cnt;
            n = n->next[c - 'a'];
        }
    }
    // Calculate the prefix count using this function.
    int count(string s) {
        auto n = &root;
        int ans = 0;
        // The ans would store the total sum of counts.
        for (char c : s) {
            ans += n->next[c - 'a']->cnt;
            n = n->next[c - 'a'];
        }
        return ans;
    }

    vector<int> sumPrefixScores(vector<string>& words) {
        int N = words.size();
        // Insert words in trie.
        for (int i = 0; i < N; i++) {
            insert(words[i]);
        }
        vector<int> scores(N, 0);
        for (int i = 0; i < N; i++) {
            // Get the count of all prefixes of given string.
            scores[i] = count(words[i]);
        }
        return scores;
    }
};

int main() {
    Solution sol;
    int r;

    sol.sumPrefixScores(vector<string>() = {"abc", "ab", "bc", "b"});
    cout << r << endl;
}