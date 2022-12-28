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

class PhoneDirectory
{
    vector<int> free, inuse;

public:
    PhoneDirectory(int maxNumbers)
    {
        for (auto i = 0; i < maxNumbers; ++i)
            free.push_back(i);
        inuse = vector<int>(maxNumbers);
    }

    int get()
    {
        if (free.empty())
            return -1;

        int rv = free.back();
        free.pop_back();
        ++inuse[rv];
        return rv;
    }

    bool check(int number)
    {
        return !inuse[number];
    }

    void release(int n)
    {
        if (inuse[n])
        {
            --inuse[n];
            free.push_back(n);
        }
    }
};

/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory* obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj->get();
 * bool param_2 = obj->check(number);
 * obj->release(number);
 */

int main()
{
    {
        PhoneDirectory pd(2);
        pd.check(0);
        pd.check(0);
        pd.check(1);

        pd.get();
        pd.check(0);
        pd.check(1);

        pd.get();
        pd.check(0);
        pd.check(1);

        pd.get();
        pd.check(0);
        pd.check(1);
    }

    {
        PhoneDirectory pd(1);
        pd.check(0);
        pd.get();
        pd.check(0);
        pd.get();
    }

    {
        PhoneDirectory pd(3);
        pd.get();
        pd.get();
        pd.check(2);
    }
}