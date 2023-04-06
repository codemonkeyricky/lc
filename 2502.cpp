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

class Allocator
{
    set<array<int, 2>> free_set;
    set<array<int, 3>> alloc; 

public:
    Allocator(int n)
    {
        free_set.insert({0, n - 1});
    }

    int allocate(int size, int id)
    {
        auto f = begin(free_set);
        while (f != end(free_set))
            if ((*f)[1] - (*f)[0] + 1 >= size)
                break;
            else 
                ++f;

        if (f == end(free_set))
            return -1;
        
        auto ff = *f;
        free_set.erase(f);
        if (ff[1] - ff[0] + 1 > size)
            free_set.insert({ff[0] + size, ff[1]});

        alloc.insert({ff[0], ff[0] + size - 1, id});
        return ff[0];
    }

    int free(int id)
    {
        auto a = begin(alloc);
        int rv = 0;
        while(a != end(alloc))
            if ((*a)[2] == id)
            {
                auto aa = *a; 
                a = alloc.erase(a);
                rv += aa[1] - aa[0] + 1;
                auto c = free_set.insert({aa[0], aa[1]}).first;
                auto cc = *c;
                if (c != begin(free_set))
                {
                    auto p = prev(c);
                    auto pp = *p;
                    if (pp[1] + 1 == cc[0])
                    {
                        free_set.erase(c), free_set.erase(p);
                        c = free_set.insert({pp[0], cc[1]}).first;
                        cc = *c;
                    }
                }
                if (next(c) != end(free_set))
                {
                    auto n = next(c); 
                    auto nn = *n;
                    if (cc[1] + 1 == nn[0])
                    {
                        free_set.erase(c), free_set.erase(n);
                        free_set.insert({cc[0], nn[1]});
                    }
                }
            }
            else
                ++a;

        return rv;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */

int main()
{
    Allocator a(10);
    cout << a.allocate(1, 1) << endl;
    cout << a.allocate(1, 2) << endl;
    cout << a.allocate(1, 3) << endl;
    cout << a.free(2) << endl;
    cout << a.allocate(3, 4) << endl;
    cout << a.allocate(1, 1) << endl;
    cout << a.allocate(1, 1) << endl;
    cout << a.free(1) << endl;
    cout << a.allocate(10, 2) << endl;
    a.free(7);
}