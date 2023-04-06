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

class MyLinkedList
{
    struct Node 
    {
        Node *next = nullptr;
        int v = -1;
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    int len = 0;

public:
    MyLinkedList()
    {
    }

    int get(int index)
    {
        auto curr = head; 
        int k = 0;
        while (k < index && curr)
            curr = curr->next, ++k;

        return curr ? curr->v : -1;
    }

    void addAtHead(int val)
    {
        Node *node = new Node(); 
        node->next = head; 
        node->v = val;

        if (!head)
            head = tail = node;
        else
            head = node;

        ++len;
    }

    void addAtTail(int val)
    {
        if (!head)
        {
            addAtHead(val);
            return;
        }

        Node *node = new Node();
        node->v = val;
        tail->next = node; 

        if (!head)
            head = tail = node;
        else
            tail = node;

        ++len;
    }

    void addAtIndex(int index, int val)
    {
        if (!head)
        {
            if (index == 0)
                addAtHead(val);
            return;
        }

        auto curr = head;
        Node *prev = nullptr;
        int k = 0;
        while (k < index && curr)
            prev = curr, curr = curr->next, ++k;

        if (k <= len)
        {
            Node *node = new Node();
            node->next = curr;
            node->v = val;
            if (index)
                prev->next = node;
            else 
                head = node;
            if (k == len)
                tail = node;
            ++len;
        }
    }

    void deleteAtIndex(int index)
    {
        if (!head)
            return;

        auto curr = head;
        Node *prev = nullptr;
        int k = 0;
        while (k < index && curr)
            prev = curr, curr = curr->next, ++k;

        if (curr)
        {
            if (index)
            {
                prev->next = curr->next;
                if (index == len - 1)
                    tail = prev;
            }
            else
                head = curr->next;

            delete curr;
            --len;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

int main()
{
    {
        MyLinkedList ll;
        ll.addAtHead(0);
        ll.addAtIndex(1, 4);
        ll.addAtTail(8);
        ll.addAtHead(5);
        ll.addAtIndex(4, 3);
        ll.addAtTail(0);
        ll.addAtTail(5);
        ll.addAtIndex(6, 3);
        ll.deleteAtIndex(7); 
        ll.deleteAtIndex(5); 
        ll.addAtTail(4);
    }

    {
        MyLinkedList ll;
        ll.addAtTail(1); 
        ll.get(0);
    }

    {
        MyLinkedList ll;
        ll.addAtIndex(0, 10); 
        ll.addAtIndex(0, 20); 
        ll.addAtIndex(1, 30);
        ll.get(0);
    }

    {
        MyLinkedList ll;
        ll.addAtHead(7);
        ll.addAtHead(2);
        ll.addAtHead(1);
        ll.addAtIndex(3, 0);
        ll.deleteAtIndex(2);
        ll.addAtHead(4);
        ll.addAtTail(4);
        ll.get(4);
    }
}