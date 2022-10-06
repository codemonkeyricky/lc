#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <cmath>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *recurse(vector<int> &tree, int k)
{
    if (k >= tree.size() || tree[k] == -1)
        return nullptr;

    return new TreeNode(tree[k], recurse(tree, k * 2 + 1), recurse(tree, k * 2 + 2));
}

TreeNode *populate(vector<int> &tree)
{
    return recurse(tree, 0);
}

class Trie
{
    struct map
    {
        int prefix;
        int end;
        array<map *, 26> letters;
    };

    map *root = nullptr;

public:
    Trie()
    {
        root = new map();
    }

    void insert(string word)
    {
        auto curr = root;
        for (auto i = 0; i < word.size(); ++i)
        {
            if (!curr->letters[word[i] - 'a'])
                curr->letters[word[i] - 'a'] = new map();
            curr = curr->letters[word[i] - 'a'];
            ++curr->prefix;
        }
        ++curr->end;
    }

    int countWordsEqualTo(string word)
    {
        auto curr = root;
        int n = word.size();
        for (auto i = 0; i < n && curr; ++i)
            curr = curr->letters[word[i] - 'a'];
        return curr ? curr->end : 0;
    }

    int countWordsStartingWith(string prefix)
    {
        auto curr = root;
        int n = prefix.size();
        for (auto i = 0; i < n && curr; ++i)
            curr = curr->letters[prefix[i] - 'a'];
        return curr ? curr->prefix : 0;
    }

    void erase(string word)
    {
        if (countWordsEqualTo(word))
        {
            auto curr = root;
            for (auto i = 0; i < word.size(); ++i)
                curr = curr->letters[word[i] - 'a'], --curr->prefix;
            --curr->end;
        }
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */

int main()
{
    {
        Trie trie;
        trie.insert("n");
        trie.insert("n");
        trie.insert("jvo");
        trie.erase("n");
        cout << trie.countWordsStartingWith("n") << endl;
        cout << trie.countWordsEqualTo("n") << endl;
    }

    // {
    //     Trie trie;
    //     trie.insert("apple");
    //     trie.insert("apple");
    //     cout << trie.countWordsEqualTo("apple") << endl;
    // }
}