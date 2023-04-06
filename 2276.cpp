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

class CountIntervals
{
    map<int, int> dp;
    int len = 0;

    int overlap(array<int, 2> &i1, array<int, 2> &i2) 
    {
        if (i1[0] > i2[0])
            swap(i1, i2);

        if (i1[1] < i2[0])
            return 0;

        if (i1[1] >= i2[1])
            return i2[1] - i2[0] + 1;

        return i1[1] - i2[0] + 1;
    }

public:
    CountIntervals()
    {
    }

    void add(int left, int right)
    {
        int no_overlap = 0;
        auto it = dp.upper_bound(left);
        if (it != begin(dp))
            it = prev(it);

        while (no_overlap < 2 && it != end(dp))
        {
            int o = overlap(array<int, 2>() = {left, right}, array<int, 2>() = {it->first, it->second});
            if (o == 0)
                ++no_overlap, ++it;
            else
            {
                len -= it->second - it->first + 1;
                left = min(left, it->first);
                right = max(right, it->second);
                it = dp.erase(it);
            }
        }

        dp[left] = right;
        len += right - left + 1;
    }

    int count()
    {
        return len;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */

int main()
{
    {
        CountIntervals ci;
        ci.add(5, 10);
        cout << ci.count() << endl;
        ci.add(3, 5);
        cout << ci.count() << endl;
    }

    // {
    //     CountIntervals ci;
    //     ci.add(33, 49);
    //     cout << ci.count() << endl;
    //     ci.add(37, 37);
    //     cout << ci.count() << endl;
    // }

    // {
    //     CountIntervals ci;
    //     ci.add(39, 44);
    //     ci.add(13, 49);
    //     cout << ci.count() << endl;
    // }

    // {
    //     CountIntervals ci;
    //     ci.add(2, 3);
    //     ci.add(7, 10);
    //     cout << ci.count() << endl;
    //     ci.add(5, 8);
    //     cout << ci.count() << endl;
    // }
}