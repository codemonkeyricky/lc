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
    int clumsy(int n)
    {
        vector<int> arr = {1};
        vector<string> op = {"*", "/", "+", "-"};
        int k = 0;
        while (n)
        {
            switch (k++ % 5)
            {
            case 0: arr.back() *= n--; break;
            case 1: arr.back() *= n--; break;
            case 2: arr.back() /= n--; break;
            case 3: arr.push_back(n--); break;
            case 4: arr.push_back(-1); break;
            }
        }
        if ((k - 1) % 5 == 4)
            arr.pop_back();
        return accumulate(begin(arr), end(arr), 0);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << sol.clumsy(13) << endl;
    cout << sol.clumsy(10) << endl;
    cout << sol.clumsy(4) << endl;
}