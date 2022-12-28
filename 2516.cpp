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
    int takeCharacters(string s, int k)
    {
        if (!k)
            return 0;

        string ss = s + s;
        int a = 0, b = 0, c = 0, rv = 1e9;
        for (auto i = 0, j = 0; j < ss.size(); ++j)
        {
            if (ss[j] == 'a')
                ++a;
            else if (ss[j] == 'b')
                ++b;
            else if (ss[j] == 'c')
                ++c;

            while (a >= k && b >= k && c >= k)
            {
                if ((i < ss.size() / 2 && j >= ss.size() / 2) || (i == 0) || (j == ss.size() / 2 - 1))
                    if (j - i + 1 <= s.size())
                        rv = min(rv, j - i + 1);

                if (ss[i] == 'a')
                    --a;
                else if (ss[i] == 'b')
                    --b;
                else if (ss[i] == 'c')
                    --c;
                ++i;
            }
        }

        return rv == 1e9 ? -1 : rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.takeCharacters("aabaaaacaabc", 2);
    cout << r << endl;
}