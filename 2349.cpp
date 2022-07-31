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

class NumberContainers
{
    unordered_map<int, set<int>> revMap;
    unordered_map<int, int> map;

public:
    NumberContainers()
    {
    }

    void change(int index, int number)
    {
        if (map.count(index))
        {
            auto n = map[index];
            revMap[n].erase(index);
            if (revMap[n].empty())
                revMap.erase(n);
        }

        map[index] = number;
        revMap[number].insert(index);
    }

    int find(int number)
    {
        return revMap.count(number) ? *revMap[number].begin() : -1;
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}