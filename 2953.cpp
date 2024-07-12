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

class Solution
{
    int substring(string &word, int k)
    {
        int n = word.size();
        int rv = 0;
        for (auto u = 1; u <= 26 && u * k <= word.size(); ++u)
        {
            array<int, 26> letters = {};
            for (int i = 0, j = 0; j < n; ++j)
            {
                ++letters[word[j] - 'a'];

                if (j >= u * k - 1)
                {
                    int pass = true;
                    for (auto l = 0; l < 26 && pass; ++l)
                        if (letters[l] && letters[l] != k)
                            pass = false;

                    if (pass)
                        ++rv;

                    --letters[word[i++] - 'a'];
                }
            }
        }
        return rv;
    }

public:
    int countCompleteSubstrings(string word, int k)
    {
        int n = word.size();
        string c(1, word[0]);
        vector<string> strings;
        for (auto i = 1; i < n; ++i)
            if (abs(word[i] - word[i - 1]) <= 2)
                c += word[i];
            else
                strings.push_back(c), c = string(1, word[i]);

        if (c.size())
            strings.push_back(c);

        int rv = 0;
        for (auto &s : strings)
            rv += substring(s, k);

        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countCompleteSubstrings("gvgvvgv", 2);
    cout << r << endl;

    r = sol.countCompleteSubstrings("aaabbbccc", 3);
    cout << r << endl;

    r = sol.countCompleteSubstrings("igigee", 2);
    cout << r << endl;
}