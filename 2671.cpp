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

class FrequencyTracker
{
    multiset<int> freq;
    unordered_map<int, int> num_to_freq;

public:
    FrequencyTracker()
    {
    }

    void add(int number)
    {
        auto f = num_to_freq[number];
        if (f)
            freq.erase(freq.find(f));
        freq.insert(++num_to_freq[number]);
    }

    void deleteOne(int number)
    {
        auto f = num_to_freq[number];
        if (f)
        {
            freq.erase(freq.find(f));
            freq.insert(--num_to_freq[number]);
        }
    }

    bool hasFrequency(int frequency)
    {
        return freq.count(frequency);
    }
};

/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker* obj = new FrequencyTracker();
 * obj->add(number);
 * obj->deleteOne(number);
 * bool param_3 = obj->hasFrequency(frequency);
 */

int main()
{
    Solution sol;
    int r;

    cout << r << endl;
}