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
    void remove(set<array<int, 2>> &set, int k)
    {
        auto c = set.upper_bound({k, (int)1e9});
        auto it = prev(c);
        int a = (*it)[0];
        int b = (*it)[1];
        pairs -= b - a;
        set.erase(it);
        if (a != b)
        {
            // first
            if (a == k)
            {
                set.insert({a + 1, b});
                pairs += b - (a + 1);
            }
            // last
            else if (b == k)
            {
                set.insert({a, b - 1});
                pairs += b - 1 - a;
            }
            // mid
            else
            {
                set.insert({a, k - 1});
                pairs += k - 1 - a;

                set.insert({k + 1, b});
                pairs += b - (k + 1);
            }
        }
    }

    void add(set<array<int, 2>> &set, int k)
    {
        auto c = set.insert({k, k}).first;

        auto n = next(c);
        // curr + 1 == next
        if (n != end(set) && (*n)[0] == k + 1)
        {
            int a = (*n)[0];
            int b = (*n)[1];
            pairs -= b - a;
            set.erase(c), set.erase(n);
            c = set.insert({a - 1, b}).first;
        }

        // prev + 1 == curr
        if (c != begin(set))
        {
            int ca = (*c)[0];
            int cb = (*c)[1];

            auto p = prev(c);
            
            int pa = (*p)[0];
            int pb = (*p)[1];

            if (pb + 1 == ca)
            {
                pairs -= pb - pa;
                set.erase(p), set.erase(c);
                c = set.insert({pa, cb}).first;
            }
        }

        int ca = (*c)[0];
        int cb = (*c)[1];
        pairs += cb - ca;
    }

    int pairs = 0;

public:
    vector<int> colorTheArray(int n, vector<vector<int>> &queries)
    {
        map<int, set<array<int, 2>>> map;
        vector<int> rv;
        vector<int> array(n);
        for (auto &q : queries)
        {
            int k = q[0], color = q[1];
            if (array[k])
                remove(map[array[k]], k);
            add(map[color], k);
            array[k] = color;
            rv.push_back(pairs);
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    vector<int> r;

    r = sol.colorTheArray(17, vector<vector<int>>() = {{11, 3}, {5, 1}, {16, 2}, {4, 4}, {5, 1}, {13, 2}, {15, 1}, {15, 3}, {8, 1}, {14, 4}, {1, 3}, {6, 2}, {8, 2}, {2, 2}, {3, 4}, {7, 1}, {10, 2}, {14, 3}, {6, 5}, {3, 5}, {5, 5}, {9, 2}, {2, 3}, {3, 3}, {4, 1}, {12, 1}, {0, 4}, {16, 4}, {8, 1}, {14, 3}, {15, 3}, {12, 1}, {11, 5}, {3, 1}, {2, 4}, {10, 1}, {14, 5}, {15, 5}, {5, 2}, {8, 1}, {6, 5}, {10, 2}});
    for (auto &c : r)
        cout << c << ", ";
    cout << endl;
}