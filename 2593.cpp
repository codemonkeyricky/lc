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
    long long findScore(vector<int> &nums)
    {
        priority_queue<array<int, 2> > q;
        int n = nums.size();
        for (auto i = 0; i < n; ++i)
            q.push({-nums[i], -i});

        set<int> marked;
        long long rv = 0;
        while (q.size())
        {
            auto [v, k] = q.top();
            k = -k;
            q.pop();
            if (!marked.count(k))
            {
                marked.insert(k);
                if (k)
                    marked.insert(k - 1);
                if (k + 1 < n)
                    marked.insert(k + 1);
                rv += v;
            }
        }
        return -rv; 
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}