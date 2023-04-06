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
    int bestClosingTime(string customers)
    {
        int yes = accumulate(begin(customers), end(customers), 0, [](int sum, char &s)
                             { return sum + (s == 'Y'); });
        int no = 0;
        int n = customers.size(); 
        int penalty = yes, k = 0;
        for (auto i = 0; i < n; ++i)
        {
            if (customers[i] == 'Y')
                --yes;
            else
                ++no;
            if (yes + no < penalty)
                penalty = yes + no, k = i + 1;
        }
        return k;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.bestClosingTime("YYNY");
    cout << r << endl;
}