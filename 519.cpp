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
    int total;
    int cols;
    int rows;
    unordered_map<int, int> map;

    Solution(int n_rows, int n_cols) : rows(n_rows), cols(n_cols), total(n_rows * n_cols)
    {
    }

    vector<int> flip()
    {
        int k = rand() % (total--);
        int i = map.count(k) ? map[k] : k;
        map[k] = map.count(total) ? map[total] : total;
        return {i / cols, i % cols};
    }

    void reset()
    {
        total = rows * cols;
        map.clear();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(m, n);
 * vector<int> param_1 = obj->flip();
 * obj->reset();
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}