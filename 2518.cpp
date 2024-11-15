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
    vector<unordered_map<int, int>> dp;

    int dfs(vector<int> &nums, int k, int sum, int kk)
    {
        int n = nums.size();
        if (k >= n)
            return sum > 0 && sum < kk;

        if (sum >= kk)
            return 0;

        if (!dp[k].count(sum))
        {
            int r0 = dfs(nums, k + 1, sum, kk);
            int r1 = dfs(nums, k + 1, sum + nums[k], kk);
            dp[k][sum] = (r0 + r1) % 1000000007;
        }
        return dp[k][sum];
    }

public:
    int countPartitions(vector<int> &nums, int k)
    {
        int n = nums.size();
        sort(begin(nums), end(nums));

        long sum = accumulate(begin(nums), end(nums), 0l);
        if (sum / 2 < k)
            return 0;

        dp = vector<unordered_map<int, int>>(n);

        int invalid = 0;
        invalid = dfs(nums, 0, 0, k);

        // (nC1 + nC2 + ... + nCn) - nCn
        long all = 1;
        for (auto i = 0; i < n; ++i)
            all = (all * 2) % 1000000007;
        all -= 2;
        all = (all - invalid * 2) % 1000000007;
        while (all < 0)
            all += 1000000007;
        return all;
    }
};

int main()
{
    Solution sol;
    int r;

    r = sol.countPartitions(vector<int>() = {367, 160, 643, 105, 915, 595, 517, 327, 57, 638, 609, 181, 595, 341, 901, 365, 990, 55, 496, 232, 840, 825, 19, 482, 910, 109, 926, 169, 1, 325, 252, 593, 11, 583, 239, 840, 928, 423, 620, 829, 706, 313, 445, 135, 981, 285, 780, 5, 678, 117, 376, 494, 383, 681, 244, 989, 780, 493, 697, 203, 810, 833, 138, 555, 411, 109, 832, 504, 325, 758, 404, 323, 709, 831, 311, 870, 360, 322, 866, 10, 959, 543, 54, 715, 638, 804, 263, 663, 441, 702, 473, 309, 279, 143, 924, 298, 712, 80, 122, 863, 880, 289, 682, 517, 471, 4, 985, 743, 501, 157, 381, 22, 914, 293, 332, 8, 604, 410, 519, 889, 162, 722, 676, 601, 910, 54, 536, 220, 89, 501, 411, 754, 409, 527, 714, 395, 915, 338, 442, 822, 70, 839, 15, 451, 937, 47, 88, 988, 608, 357, 385, 952, 766, 917, 543, 810, 217, 47, 717, 306, 201, 91, 93, 135, 418, 56, 519, 269, 855, 755, 98, 735, 414, 742, 552, 885, 183, 694, 463, 292, 318, 239, 459, 763, 698, 447, 506, 657, 108, 185, 666, 697, 849, 782, 461, 285, 950, 704, 951, 846, 86, 600, 429, 111, 520, 14, 576, 591, 602, 678, 961, 2, 766, 710, 643, 385, 465, 66, 748, 528, 758, 1, 54, 969, 635, 588, 625, 44, 927, 921, 9, 50, 632, 77, 735, 977, 521, 64, 282, 362, 996, 561, 125, 319, 556, 209, 855, 280, 613, 432, 93, 126, 427, 780, 969, 933, 809, 637, 294, 225, 367, 351, 290, 406, 35, 460, 153, 625, 695, 77, 389, 279, 648, 804, 65, 624, 405, 428, 49, 851, 515, 449, 340, 43, 708, 405, 201, 283, 779, 201, 306, 707, 372, 15, 971, 566, 828, 819, 537, 747, 730, 764, 141, 248, 768, 195, 986, 834, 775, 719, 969, 23, 866, 724, 780, 24, 744, 727, 53, 414, 100, 246, 506, 364, 315, 142, 516, 66, 947, 669, 272, 753, 621, 169, 73, 169, 930, 345, 767, 555, 82, 806, 312, 552, 57, 432, 759, 942, 339, 385, 242, 297, 120, 785, 443, 843, 642, 224, 873, 556, 278, 855, 273, 803, 597, 288, 478, 300, 894, 462, 354, 901, 366, 489, 664, 551, 758, 727, 528, 276, 228, 890, 602, 768, 752, 577, 586, 92, 97, 956, 688, 438, 501, 372, 20, 352, 308, 923, 545}, 787);
    cout << r << endl;

    r = sol.countPartitions(vector<int>() = {96, 40, 22, 98, 9, 97, 45, 22, 79, 57, 95, 62}, 505);
    cout << r << endl;

    r = sol.countPartitions(vector<int>() = {790, 555, 729, 447, 538, 657, 258, 716, 645, 349, 148, 860, 425, 401, 282, 889, 309, 720, 228, 39, 366, 107, 765, 546, 791, 938, 154, 85, 845, 656}, 558);
    cout << r << endl;

    r = sol.countPartitions(vector<int>() = {977208288, 291246471, 396289084, 732660386, 353072667, 34663752, 815193508, 717830630, 566248717, 260280127, 824313248, 701810861, 923747990, 478854232, 781012117, 525524820, 816579805, 861362222, 854099903, 300587204, 746393859, 34127045, 823962434, 587009583, 562784266, 115917238, 763768139, 393348369, 3433689, 586722616, 736284943, 596503829, 205828197, 500187252, 86545000, 490597209, 497434538, 398468724, 267376069, 514045919, 172592777, 469713137, 294042883, 985724156, 388968179, 819754989, 271627185, 378316864, 820060916, 436058499, 385836880, 818060440, 727928431, 737435034, 888699172, 961120185, 907997012, 619204728, 804452206, 108201344, 986517084, 650443054}, 95);
    cout << r << endl;

    r = sol.countPartitions(vector<int>() = {6, 6}, 2);
    cout << r << endl;

    r = sol.countPartitions(vector<int>() = {1, 2, 3, 4}, 4);
    cout << r << endl;
}