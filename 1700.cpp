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
    int countStudents(vector<int> &students, vector<int> &sandwiches)
    {
        int a[] = {0, 0};
        for (int i = 0; i < students.size(); i++)
            a[students[i]] += 1;
        int k = 0;
        while (k < sandwiches.size())
        {
            if (a[sandwiches[k]] > 0)
                a[sandwiches[k]] -= 1;
            else
                break;
            k += 1;
        }
        return sandwiches.size() - k;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countStudents(vector<int>() = {1, 1, 1, 0, 0, 1}, vector<int>() = {1, 0, 0, 0, 1, 1});
    cout << r << endl;
}