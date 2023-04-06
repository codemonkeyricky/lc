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
    long long maxScore(vector<int> &nums1, vector<int> &nums2, int k)
    {
        long long rv = 0, sum = 0, n = nums1.size();
        map<int, vector<int>> cnt;
        for (auto i = 0; i < n; ++i)
            cnt[nums2[i]].push_back(nums1[i]);

        priority_queue<int> q;
        for (auto it = rbegin(cnt); it != rend(cnt); ++it)
        {
            for (auto &v : it->second)
            {
                if (q.size() >= k && -q.top() < v)
                    sum -= -q.top(), q.pop();
                if (q.size() < k)
                    sum += v, q.push(-v);
            }
            if (q.size() >= k)
                rv = max(rv, sum * it->first);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.maxScore(vector<int>() = {4, 2, 3, 1, 1}, vector<int>() = {7, 5, 10, 9, 6}, 1);
    cout << r << endl;

    r = sol.maxScore(vector<int>() = {1, 3, 3, 2}, vector<int>() = {2, 1, 3, 4}, 3);
    cout << r << endl;
}