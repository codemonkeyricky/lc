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
    vector<vector<string>> mostPopularCreator(vector<string> &creators, vector<string> &ids, vector<int> &views)
    {
        unordered_map<string, long> viewSum;
        unordered_map<string, vector<pair<long, string>>> videos;
        int n = creators.size();
        for (auto i = 0; i < n; ++i)
        {
            viewSum[creators[i]] += views[i];
            videos[creators[i]].push_back({views[i], ids[i]});
        }

        vector<pair<int, string>> sumView;
        for (auto &d : viewSum)
            sumView.push_back({d.second, d.first});
        sort(begin(sumView), end(sumView));

        vector<vector<string>> rv;
        int count = rbegin(sumView)->first;
        for (auto it = rbegin(sumView); it != rend(sumView) && it->first == count; ++it)
        {
            auto creator = it->second;
            sort(begin(videos[creator]), end(videos[creator]), [](const pair<int, string> &l, const pair<int, string> &r) {
                if(l.first > r.first)
                    return true;
                else if (l.first == r.first)
                    return l.second < r.second;
                return false; 
            });

            rv.push_back({creator, videos[creator][0].second});
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    int r;

    sol.mostPopularCreator(vector<string>() = {"alice", "bob", "alice", "chris"}, vector<string>() = {"one", "two", "three", "four"}, vector<int>() = {5, 10, 5, 4});
}