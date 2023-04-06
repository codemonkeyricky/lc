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
    vector<int> getStrongest(vector<int> &arr, int k)
    {
        sort(begin(arr), end(arr));
        int m = (arr.size() - 1) / 2;
        int i = 0, j = arr.size() - 1;
        vector<int> rv; 
        while (k)
        {
            int a = abs(arr[i] - arr[m]);
            int b = abs(arr[j] - arr[m]);
            if (a <= b)
                rv.push_back(arr[j--]);
            else 
                rv.push_back(arr[i++]);
            --k;
        }
        return rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}