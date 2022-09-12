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
    void dfs(vector<int> &s, vector<int> &d, int k, vector<vector<int>> &al, vector<int> &seen, unordered_map<int, int> &cnt)
    {
        if (!seen[k])
        {
            seen[k] = true;
            ++cnt[s[k]];
            --cnt[d[k]];
            for (auto &v : al[k])
                dfs(s, d, v, al, seen, cnt);
        }
    }

public:
    int minimumHammingDistance(vector<int> &source, vector<int> &target, vector<vector<int>> &allowedSwaps)
    {
        // sort(begin(source), end(source));
        // sort(begin(target), end(target));

        int n = source.size();
        vector<vector<int>> al(n);
        for (auto &swap : allowedSwaps)
            al[swap[0]].push_back(swap[1]), al[swap[1]].push_back(swap[0]);
        
        vector<int> seen(n);
        int rv = 0;
        for (auto i = 0; i < n; ++i)
            if (!seen[i])
            {
                unordered_map<int, int> cnt;
                dfs(source, target, i, al, seen, cnt);
                int r = 0;
                for (auto &c : cnt)
                    r += abs(c.second);
                rv += r / 2;
            }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.minimumHammingDistance(vector<int>() = {41, 37, 51, 100, 25, 33, 90, 49, 65, 87, 11, 18, 15, 18},
                                   vector<int>() = {41, 92, 69, 75, 29, 13, 53, 21, 17, 81, 33, 19, 33, 32},
                                   vector<vector<int>>() = {{0, 11}, {5, 9}, {6, 9}, {5, 7}, {8, 13}, {4, 8}, {12, 7}, {8, 2}, {13, 5}, {0, 7}, {6, 4}, {8, 9}, {4, 12}, {6, 1}, {10, 0}, {10, 2}, {7, 3}, {11, 10}, {5, 2}, {11, 1}, {3, 0}, {8, 5}, {12, 6}, {2, 1}, {11, 2}, {4, 9}, {2, 9}, {10, 6}, {12, 10}, {4, 13}, {13, 2}, {11, 9}, {3, 6}, {0, 4}, {1, 10}, {5, 11}, {12, 1}, {10, 4}, {6, 2}, {10, 7}, {3, 13}, {4, 5}, {13, 10}, {4, 7}, {0, 12}, {9, 10}, {9, 3}, {0, 5}, {1, 9}, {5, 10}, {8, 0}, {12, 11}, {11, 4}, {7, 9}, {7, 2}, {13, 9}, {12, 3}, {8, 6}, {7, 6}, {8, 12}, {4, 3}, {7, 13}, {0, 13}, {2, 0}, {3, 8}, {8, 1}, {13, 6}, {1, 4}, {0, 9}, {2, 3}, {8, 7}, {4, 2}, {9, 12}});
    cout << r << endl;
}