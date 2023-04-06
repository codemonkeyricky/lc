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

class Robot
{
public:
    int st = 0, w = 0, h = 0, moved = false;
    Robot(int width, int height) : w(width - 1), h(height - 1) {}
    void move(int num)
    {
        moved = true;
        st = (st + num) % (2 * h + 2 * w);
    }
    vector<int> getPos()
    {
        return {st < w ? st : st < w + h   ? w
                          : st < 2 * w + h ? 2 * w + h - st
                                           : 0,
                st < w ? 0 : st < w + h   ? st - w
                         : st < 2 * w + h ? h
                                          : 2 * w + 2 * h - st};
    }
    string getDir()
    {
        return (moved && (st > 2 * w + h || st == 0)) ? "South" : st <= w   ? "East"
                                                              : st <= w + h ? "North"
                                                                            : "West";
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */

int main()
{
    Robot r(6, 3);

    r.step(2);
    r.step(2);
    cout << r.getPos()[0] << ", " << r.getPos()[1] << endl;
    r.step(2);
    r.step(1);
    r.step(4);
    cout << r.getPos()[0] << ", " << r.getPos()[1] << endl;
}