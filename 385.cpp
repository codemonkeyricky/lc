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


// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger
{
public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution
{
    NestedInteger dfs(string s, int &i)
    {
        NestedInteger ni;
        int n = s.size();
        string num;
        for (; i < n; ++i)
            if (s[i] == '[' && ++i)
                ni.add(dfs(s, i));
            else if (s[i] == ']')
            {
                if (num.size())
                    ni.add(NestedInteger(stoi(num)));
                return ni;
            }
            else if (s[i] == ',')
            {
                if (num.size())
                    ni.add(NestedInteger(stoi(num))), num.clear();
            }
            else
                num += s[i];

        if (num.size())
            ni.setInteger(stoi(num));
        return ni;
    }

public:
    NestedInteger deserialize(string s)
    {
        int k = s[0] == '[' ? 1 : 0;
        return dfs(s, k);
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}