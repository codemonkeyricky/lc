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
    int visibleMountains(vector<vector<int>> &peaks)
    {
        map<vector<int>, int> dup;
        for (auto &p : peaks)
            ++dup[p];
        
        vector<vector<int>> peaks2;
        for (auto &p : peaks)
            if (dup[p] == 1)
                peaks2.push_back(p);

        swap(peaks2, peaks);
        sort(begin(peaks), end(peaks));
                
        int n = peaks.size();
        vector<array<int, 2>> stack;
        for (auto i = 0; i < n; ++i)
        {
            auto x = peaks[i][0], y = peaks[i][1];
            while (stack.size() && y - x >= stack.back()[1] - stack.back()[0])
                stack.pop_back();

            if (stack.empty() || x + y > stack.back()[0] + stack.back()[1])
                stack.push_back({x, y});
        }

        return stack.size();
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.visibleMountains(vector<vector<int>>() = {{38, 26}, {3, 32}, {2, 1}});
    cout << r << endl;
}