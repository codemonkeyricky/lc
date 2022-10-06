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
public:
    bool equalFrequency(string word)
    {
        array<int, 26> chars = {};
        for (auto &c : word)
            ++chars[c - 'a'];

        for (auto i = 0; i < 26; ++i)
            if (chars[i])
            {
                auto copy = chars;
                --chars[i];
                int freq = -1, j = 0;
                for (; j < 26; ++j)
                    if (chars[j])
                        if (freq == -1)
                            freq = chars[j];
                        else if (chars[j] != freq)
                            break;
                if (j >= 26)
                    return true;
                
                chars = copy;
            }

        return false; 
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.equalFrequency("aazz");
    cout << r << endl;

    r = sol.equalFrequency("abcc");
    cout << r << endl;
}