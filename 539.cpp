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
    int findMinDifference(vector<string> &timePoints)
    {
        vector<int> time;
        for (auto &s : timePoints)
            time.push_back(stoi(s.substr(0, 2)) * 60 + stoi(s.substr(3)));

        sort(begin(time), end(time));
        int rv = 1e9;

        for (auto i = 1; i < time.size(); ++i)
            rv = min(rv, time[i] - time[i - 1]);

        return min(rv, 1440 + time[0] - time.back());
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}