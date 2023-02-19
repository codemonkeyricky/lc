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

/**
 * Definition for polynomial singly-linked list.
 * struct PolyNode {
 *     int coefficient, power;
 *     PolyNode *next;
 *     PolyNode(): coefficient(0), power(0), next(nullptr) {};
 *     PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
 *     PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
 * };
 */

class Solution
{
public:
    PolyNode *addPoly(PolyNode *poly1, PolyNode *poly2)
    {
        PolyNode *head = nullptr, *curr = nullptr, *prev = nullptr;
        while (poly1 || poly2)
        {
            if (poly1 && poly2)
            {
                if (poly1->power > poly2->power)
                {
                    if (!head)
                        head = curr = poly1;
                    else
                        prev->next = curr = poly1;
                    poly1 = poly1->next;
                }
                else if (poly1->power < poly2->power)
                {
                    if (!head)
                        head = curr = poly2;
                    else
                        prev->next = curr = poly2;
                    poly2 = poly2->next;
                }
                else 
                {
                    if (poly1->coefficient + poly2->coefficient != 0)
                    {
                        poly1->coefficient += poly2->coefficient;
                        if (!head)
                            head = curr = poly1;
                        else
                            prev->next = curr = poly1;
                    }
                    else 
                    {
                        if (!poly1->next && !poly2->next)
                            if (prev)
                                prev->next = nullptr;
                    }

                    poly1 = poly1->next; 
                    poly2 = poly2->next; 
                }

                prev = curr; 
            }
            else if (poly1)
            {
                if (!head)
                    head = curr = poly1;
                else
                    prev->next = curr = poly1;
                break;
            }
            else 
            {
                if (!head)
                    head = curr = poly2;
                else
                    prev->next = curr = poly2;
                break;
            }
        }

        return head;
    }
};

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}