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
    string shiftingLetters(string s, vector<vector<int>> &shifts)
    {
        int n = s.size();
        vector<int> shift(n + 1);
        for (auto &s : shifts)
        {
            int i = s[0], j = s[1] + 1;
            shift[i] += s[2] ? 1 : -1, shift[j] += s[2] ? -1 : 1;
        }

        for (auto i = 0, offset = 0; i < shift.size() - 1; ++i)
        {
            offset += shift[i];
            auto k = s[i] - 'a';
            k = (k + offset) % 26;
            if (k < 0)
                k += 26;
            s[i] = k + 'a';
        }

        return s;
    }
};

int main()
{
    Solution sol;
    string r;

    r = sol.shiftingLetters("xuwdbdqik", vector<vector<int>>() = {{4, 8, 0}, {4, 4, 0}, {2, 4, 0}, {2, 4, 0}, {6, 7, 1}, {2, 2, 1}, {0, 2, 1}, {8, 8, 0}, {1, 3, 1}});
    cout << r << endl;

    r = sol.shiftingLetters("abc", vector<vector<int>>() = {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}});
    cout << r << endl;
}