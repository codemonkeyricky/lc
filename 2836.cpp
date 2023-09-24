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
    void dfs(vector<int> &recevier, int k, int d, vector<int> &curr, vector<int> &seen)
    {
        if (seen[k] == 1)
        {
            // loop detected

            // Find loop entry
            int i = 0;
            for (; i < curr.size(); ++i)
                if (curr[i] == k)
                    break;

            vector<array<int, 2>> loop;
            int ii = i;
            for (; i < curr.size(); ++i)
                loop.push_back({curr[i], 0});

            int kk = _k % loop.size();
            long long sum = 0, max_start = 0;
            for (auto i = 0; i < loop.size() * 2; ++i)
            {
                sum += loop[i % loop.size()][0];
                if (i >= kk)
                {
                    auto pk = (i - kk + loop.size()) % loop.size();
                    loop[pk][1] = sum;
                    sum -= loop[pk][0];
                    max_start = max(sum, max_start);
                }
            }

            sum = 0;
            for (auto i = 0; i < loop.size(); ++i)
                sum += loop[i][0];

            _rv = max(_rv, sum * (_k / (long long)loop.size()) + max_start);

            auto it = loops.insert(loop).first;
            for (i = ii; i < curr.size(); ++i)
                loop_iter[curr[i]] = {it, sum};
        }
        else if (seen[k] == 0)
        {
            seen[k] = 1;
            curr.push_back(k);
            dfs(recevier, recevier[k], d + 1, curr, seen);
            curr.pop_back();
            seen[k] = 2;
        }
    }

    long long loop_score(int k, int d)
    {
        auto it = loop_iter[k].first;
        auto dd = d % it->size();
        long long a = 0, b = 0;
        if (it->size() > 1)
            a = (*it)[dd][1];
        b = d / it->size() * loop_iter[k].second;
        return a + b;
    }

    pair<set<vector<array<int, 2>>>::iterator, int> dfs2(vector<int> &receiver, vector<int> &sum, int k, int d, vector<int> &seen)
    {
        if (loop_iter.count(k))
            return {loop_iter[k].first, k};

        sum.push_back(k + (sum.size() ? sum.back() : 0));
        auto [it, entry_k] = dfs2(receiver, sum, receiver[k], d + 1, seen);
        long long a = 0, b = 0;
        if (sum.size() - d < _k)
        {
            a = sum.back() - (d ? sum[d - 1] : 0);
            b = loop_score(entry_k, _k - (sum.size() - d));
            _rv = max(_rv, a + b);
        }
        else
        {
            _rv = max(_rv, (long long)sum[d + _k] - (d ? sum[d - 1] : 0));
        }

        return {it, entry_k};
    }

    set<vector<array<int, 2>>> loops;
    map<int, pair<set<vector<array<int, 2>>>::iterator, int>> loop_iter; // index / pair[ loop iterator, sum ]
    long long _k = 0;
    long long _rv = 0;

public:
    long long getMaxFunctionValue(vector<int> &receiver, long long k)
    {
        int n = receiver.size();
        _k = k + 1;

        // TODO: iterate all nodes to find all loops
        vector<int> seen(n);
        for (auto i = 0; i < n; ++i)
        {
            vector<int> curr; 
            dfs(receiver, i, 0, curr, seen);
        }

        // Find all leaves
        set<int> leaves;
        for (auto i = 0; i < n; ++i)
            leaves.insert(i);
        for (auto i = 0; i < n; ++i)
            leaves.erase(receiver[i]);

        seen = vector<int>(n);
        for (auto &leaf : leaves)
        {
            vector<int> sum;
            dfs2(receiver, sum, leaf, 0, seen);
        }

        return _rv;
    }
};

int main()
{
    {
        Solution sol;
        int r;
        r = sol.getMaxFunctionValue(vector<int>() = {1, 0, 0}, 6);
        cout << r << endl;
    }

    {
        Solution sol;
        int r;
        r = sol.getMaxFunctionValue(vector<int>() = {1, 1, 1, 2, 3}, 3);
        cout << r << endl;
    }

    {
        Solution sol;
        int r;
        r = sol.getMaxFunctionValue(vector<int>() = {2, 0, 1}, 4);
        cout << r << endl;
    }
}