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

class MKAverage
{
    vector<multiset<long>> set;
    long sum[3], k, m;
    queue<long> q;

    void balance()
    {
        long kk[2] = {k, m - 2 * k};
        for (auto i = 0; i < 2; ++i)
        {
            if (set[i].size() > kk[i])
            {
                auto plast = *prev(end(set[i]));

                set[i + 1].insert(plast);
                sum[i + 1] += plast;

                set[i].erase(set[i].find(plast));
                sum[i] -= plast;
            }
            else if (set[i].size() == kk[i])
            {
                if (set[i + 1].size())
                {
                    auto plast = *prev(end(set[i]));
                    auto nbeg = *begin(set[i + 1]);
                    if (plast > nbeg)
                    {
                        set[i + 1].erase(begin(set[i + 1]));
                        sum[i + 1] -= nbeg;
                        set[i + 1].insert(plast);
                        sum[i + 1] += plast;

                        set[i + 0].erase(prev(begin(set[i + 0])));
                        sum[i + 0] -= plast;
                        set[i + 0].insert(nbeg);
                        sum[i + 0] += nbeg;
                    }
                }
            }
        }
    }

public:
    MKAverage(int m, int k) : k(k), m(m)
    {
        set = vector<multiset<long>>(3);
        sum[0] = sum[1] = sum[2] = 0;
    }

    void addElement(int num)
    {
        if (q.size() == m)
            for (auto i = 0; i < 3; ++i)
                if (set[i].count(q.front()))
                {
                    set[i].erase(set[i].find(q.front()));
                    sum[i] -= q.front();
                    break;
                }

        if (q.size() == m)
            q.pop();
        q.push(num);

        set[0].insert(num);
        sum[0] += num;
        balance();
    }

    int calculateMKAverage()
    {
        auto ss = 0;
        for(auto i = 0; i < 3; ++i)
            ss += set[i].size();
        if (ss < m)
            return -1;

        return sum[1] / (m - 2 * k);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */

int main()
{
    {
        MKAverage mk(6, 1);
        mk.addElement(3);
        mk.addElement(1);
        mk.addElement(12);
        mk.addElement(5);
        mk.addElement(3);
        mk.addElement(4);
    }

    {
        MKAverage mk(3, 1);
        mk.addElement(3);
        mk.addElement(1);
        mk.addElement(5);
        mk.addElement(5);
        mk.addElement(5);
    }
}