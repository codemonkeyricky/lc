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
    bool haveConflict(vector<string> &evt1, vector<string> &evt2)
    {
        if (evt2 < evt1)
            swap(evt1, evt2);

        auto end = stoi(evt1[1].substr(0, 2)) * 60;
        end += stoi(evt1[1].substr(3));
        auto start = stoi(evt2[0].substr(0, 2)) * 60;
        start += stoi(evt2[0].substr(3));

        return end >= start;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}