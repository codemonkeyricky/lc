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

class LockingTree
{
    vector<vector<int>> tree;
    vector<int> locks;
    vector<int> p;

    bool dfs(int n)
    {
        if (locks[n] != -1)
            return true;
        for (auto &n : tree[n])
            if (dfs(n))
                return true;
        return false;
    }

    void unlockAll(int n)
    {
        locks[n] = -1;
        for (auto &nn : tree[n])
            unlockAll(nn);
    }

public:
    LockingTree(vector<int> &parent)
    {
        int n = parent.size();
        tree = vector<vector<int>>(n);
        for (auto i = 0; i < n; ++i)
            if (parent[i] != -1)
                tree[parent[i]].push_back(i);
        locks = vector<int>(10001, -1);
        p = parent;
    }

    bool lock(int num, int user)
    {
        if (locks[num] == -1)
        {
            locks[num] = user;
            return true;
        }
        return false;
    }

    bool unlock(int num, int user)
    {
        if (locks[num] == user)
        {
            locks[num] = -1;
            return true;
        }
        return false;
    }

    bool upgrade(int num, int user)
    {
        /*
         *  Current node unlocked. 
         */
        if (locks[num] != -1)
            return false;

        /*
         *  No locked ancestors.
         */ 
        auto c = num;
        while (p[c] != -1 && locks[c] == -1)
            c = p[c];
        if (locks[c] != -1)
            return false;

        /*
         *  Find one locked descendent. 
         */
        if (!dfs(num))
            return false;

        unlockAll(num);

        lock(num, user);

        return true;
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */

int main()
{
    vector<int> p = {-1, 0, 3, 1, 0};
    LockingTree lt(p);
    lt.upgrade(4, 5);
}