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

class MyStack
{
    queue<int> q[2];
    int back = -1;

public:
    MyStack()
    {
    }

    void push(int x)
    {
        q[0].push(x);
        back = x;
    }

    int pop()
    {
        while (q[0].size() > 1)
            q[1].push(q[0].front()), q[0].pop();
        int rv = q[0].front();
        q[0].pop();
        swap(q[0], q[1]);
        return rv;
    }

    int top()
    {
        auto rv = pop();
        push(rv);
        return rv;
    }

    bool empty()
    {
        return q[0].empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main()
{
    MyStack sol;

    sol.push(1);
    sol.push(2);
    cout << sol.top() << endl;
    cout << sol.pop() << endl;
    cout << sol.empty() << endl;
}