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
    string capitalizeTitle(string title)
    {
        int n = title.size();
        for (auto i = 0; i < n; ++i)
            if (i == 0 || title[i - 1] == ' ')
            {
                if ((i + 1 < title.size() && title[i + 1] == ' ') || (i + 2 < title.size() && title[i + 2] == ' ') || n - i <= 2)
                    title[i] = tolower(title[i]);
                else 
                    title[i] = toupper(title[i]);
            }
            else
                title[i] = tolower(title[i]);
        return title;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}