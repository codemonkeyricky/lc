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

class ValidWordAbbr
{
    map<string, int> abbrev;
    unordered_set<string> input; 

public:
    ValidWordAbbr(vector<string> &dictionary)
    {
        input = unordered_set<string>(begin(dictionary), end(dictionary));
        dictionary.assign(begin(input), end(input));

        for (auto &word : dictionary)
        {
            int l = word.size() - 2;
            if (l <= 0)
                ++abbrev[word];
            else
                ++abbrev[word[0] + to_string(l) + word.back()];
        }
        input = unordered_set<string>(begin(dictionary), end(dictionary));
    }

    bool isUnique(string word)
    {
        int l = word.size() - 2;
        string ab;
        if (l <= 0)
            ab = word; 
        else
            ab = word[0] + to_string(l) + word.back();

        if (input.count(word))
            return abbrev[ab] == 1;
        return !abbrev.count(ab);
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */

int main()
{
    vector<string> init = {"deer", "door", "cake", "card"};
    ValidWordAbbr vwa(init);
    cout << vwa.isUnique("dear") << endl;
    cout << vwa.isUnique("cart") << endl;
}