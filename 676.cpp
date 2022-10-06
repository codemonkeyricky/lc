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

class MagicDictionary
{
    unordered_map<string, unordered_set<string>> match;
public:
    MagicDictionary()
    {
    }

    void buildDict(vector<string> dictionary)
    {
        for (auto &word : dictionary)
        {
            for (auto i = 0; i < word.size(); ++i)
            {
                auto copy = word; 
                copy[i] = '*';
                match[copy].insert(word); 
            }
        }
    }

    bool search(string word)
    {
        for (auto i = 0; i < word.size(); ++i)
        {
            auto copy = word; 
            copy[i] = '*';
            if (match.count(copy) && (!match[copy].count(word) || (match[copy].count(word) && match[copy].size() > 1)))
                return true;
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}