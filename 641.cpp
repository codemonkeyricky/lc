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

class MyCircularDeque
{
    vector<int> q;
    int head, tail;

    int prev(int k)
    {
        if (--k < 0)
            k += q.size();
        return k;
    }

    int next(int k)
    {
        if (++k >= q.size())
            k %= q.size();
        return k;
    }

public:
    MyCircularDeque(int k)
    {
        head = tail = 0;
        q = vector<int>(k, -1);
    }

    bool insertFront(int value)
    {
        if (prev(head) == tail)
            return false;

        if (head == tail)
        {
            if (q[head] == -1)
                q[head] = value;
            else
                head = prev(head), q[head] = value;
        }
        else 
        {
            head = prev(head), q[head] = value;
        }

        return true;
    }

    bool insertLast(int value)
    {
        if (prev(head) == tail)
            return false;

        if (head == tail)
        {
            if (q[head] == -1)
                q[head] = value;
            else
                tail = next(head), q[tail] = value;
        }
        else
            tail = next(tail), q[tail] = value;

        return true;
    }

    bool deleteFront()
    {
        if (q[head] == -1)
            return false;

        q[head] = -1;
        if (head != tail)
            head = next(head);

        return true;
    }

    bool deleteLast()
    {
        if (q[tail] == -1)
            return false;

        q[tail] = -1;
        if (head != tail)
            tail = prev(tail);

        return true;
    }

    int getFront()
    {
        return q[head];
    }

    int getRear()
    {
        return q[tail];
    }

    bool isEmpty()
    {
        return head == tail && q[head] == -1;
    }

    bool isFull()
    {
        return prev(head) == tail;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

int main()
{
    {
        MyCircularDeque q(5);
        q.insertFront(7);
        q.insertLast(0);
        cout << q.getFront() << endl;
        q.insertLast(3);
        cout << q.getFront() << endl;
        q.insertFront(9);
        cout << q.deleteLast() << endl;
        cout << q.getRear() << endl;
    }

    // {
    //     MyCircularDeque q(3);
    //     q.insertLast(1);
    //     q.insertLast(2);
    //     q.insertFront(3);
    //     q.insertFront(4);
    //     cout << q.getRear() << endl;
    //     cout << q.isFull() << endl;
    //     cout << q.deleteLast() << endl;
    //     cout << q.insertFront(4) << endl;
    //     cout << q.getFront() << endl;
    // }
}