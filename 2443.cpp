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

unordered_map<int, int> lookup;
class Solution
{
public:
    bool sumOfNumberAndReverse(int num)
    {
        for (auto i = 0; i <= num; ++i)
        {
            string s;
            if (!lookup.count(i))
            {
                s = to_string(i);
                reverse(begin(s), end(s));
                lookup[i] = stoi(s);
            }
            auto ri = lookup[i];
            if (i + ri == num)
                return true;
        }
        return false;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}