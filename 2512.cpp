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

class Solution
{
public:
    vector<int> topStudents(vector<string> &positive, vector<string> &negative, vector<string> &report, vector<int> &id, int k)
    {
        unordered_set<string> pos(begin(positive), end(positive)), neg(begin(negative), end(negative));
        map<int, int> rank;
        string word; 
        for (auto i = 0; i < report.size(); ++i)
            for(auto j = 0; j <= report[i].size(); ++j)
                if (j == report[i].size() || report[i][j] == ' ')
                {
                    if (pos.count(word))
                        rank[id[i]] += 3;
                    else if(neg.count(word)) 
                        rank[id[i]] -= 1;
                    word.clear();
                }
                else
                    word += report[i][j];
        vector<array<int, 2>> rr;
        for (auto &r : rank)
            rr.push_back({r.second, r.first});
        sort(begin(rr), end(rr), [](const array<int, 2> &l, const array<int, 2> &r) {
                 if (l[0] == r[0])
                     return l[1] < r[1];
                 return l[0] >= r[0];
             });

        vector<int> rv;
        for (auto i = 0; i < k; ++i)
            rv.push_back(rr[i][1]);
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.topStudents(vector<string>() = {"smart", "brilliant", "studious"},
                    vector<string>() = {"not"},
                    vector<string>() = {"this student is studious", "the student is smart"},
                    vector<int>() = {1, 2},
                    2);
}