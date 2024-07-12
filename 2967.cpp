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

vector<int> palin;
class Solution
{
    void dfs(string s, vector<int> &palin)
    {
        // if (s == "413181314")
        //     volatile int a = 0;

        if (s.size() > 9)
            return;
        if (s.size() && stol(s) > 10e9)
            return;
        if (s.size() && s[0] != '0')
        {
            // if (stoi(s) == 413181314)
            //     assert(0);
            palin.push_back(stoi(s));
        }

        for (auto i = 0; i < 10; ++i)
            dfs(string(1, i + '0') + s + string(1, i + '0'), palin);
    }

public:
    long long minimumCost(vector<int> &nums)
    {
        if (palin.empty())
        {
            palin.push_back(0);
            for (auto i = 0; i < 10; ++i)
                dfs(string(1, i + '0'), palin);
            dfs("", palin);
            sort(begin(palin), end(palin));
        }

        sort(begin(nums), end(nums));

        long long rv = __LONG_LONG_MAX__; 
        for (auto &p : palin)
        {
            long long r = 0;
            for (auto &n : nums)
                r += abs(n - p);

            if (r < rv)
                rv = r;
        }
        return rv;
    }
};

int main()
{
    Solution sol;
    long long r;

    r = sol.minimumCost(vector<int>() = {493394, 291777192, 2521252, 443787344, 152959251, 531656135, 144868441, 563777365, 3527253, 227020722, 250868052, 5762675, 899191998, 4694964, 358838853, 641747146, 231404132, 85155158, 371141173, 656191656, 722060227, 877474778, 324878423, 414848414, 92029, 940282049, 95844859, 50511505, 997919799, 827565728, 731373137, 654222456, 790151097, 5121215, 733424337, 3600063, 945252549, 140626041, 563252365, 249717942, 930585039, 363151363, 905797509, 447090744, 622020226, 303616303, 411525114, 68222286, 900272009, 642949246, 21244212, 321878123, 908373809, 951434159, 645070546, 292878292, 430151034, 56277265, 824212428, 395373593, 845454548, 468202864, 2038302, 542202245, 168111861, 260969062, 203656302, 8138318, 625909526, 448858844, 318030813, 7821287, 120666021, 825303528, 217848712, 51199115, 639585936, 79397, 556383655, 730434037, 1272721, 1321231, 431777134, 304333403, 148515841, 69844896, 786434687, 778717877, 754242457, 446323644, 462141264, 991626199, 402939204, 85866858, 692464296, 685585586, 502373205, 611828116, 631727136, 236767632});
    cout << r << endl;

    r = sol.minimumCost(vector<int>() = {206, 215, 216, 219, 220, 221});
    cout << r << endl;

    r = sol.minimumCost(vector<int>() = {203, 207, 209, 210, 217, 219});
    cout << r << endl;

    r = sol.minimumCost(vector<int>() = {101, 102, 105, 120, 124});
    cout << r << endl;

    r = sol.minimumCost(vector<int>() = {1, 2, 3, 4, 5});
    cout << r << endl;
}