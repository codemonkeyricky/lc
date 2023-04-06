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

class ThroneInheritance
{
    struct Person
    {
        Person(string name) : name(name) {}
        string name;
        vector<Person *> children;
    };

    Person *king;
    unordered_map<string, Person *> map;

    void dfs(Person *p, vector<string> &rv)
    {
        if (p->name.size())
            rv.push_back(p->name);
        for (auto &c : p->children)
            dfs(c, rv);
    }

public:
    ThroneInheritance(string kingName)
    {
        king = new Person(kingName);
        map[kingName] = king;
    }

    void birth(string parentName, string childName)
    {
        auto p = new Person(childName);
        map[parentName]->children.push_back(p);
        map[childName] = p;
    }

    void death(string name)
    {
        map[name]->name = "";
    }

    vector<string> getInheritanceOrder()
    {
        vector<string> rv;
        dfs(king, rv);
        return rv; 
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}