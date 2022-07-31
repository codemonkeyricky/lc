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

class FoodRatings
{
    unordered_map<string, map<int, set<string>>> m;
    unordered_map<string, int> foodRating;
    unordered_map<string, string> foodCuisine; 

public:
    FoodRatings(vector<string> &foods, vector<string> &cuisines, vector<int> &ratings)
    {
        int n = foods.size();
        for(auto i = 0 ; i < n; ++i)
        {
            m[cuisines[i]][ratings[i]].insert(foods[i]);
            foodRating[foods[i]] = ratings[i];
            foodCuisine[foods[i]] = cuisines[i];
        }
        
    }

    void changeRating(string food, int newRating)
    {
        auto rating = foodRating[food];
        auto cuisine = foodCuisine[food];
        foodRating[food] = newRating;

        m[cuisine][rating].erase(food);
        if (m[cuisine][rating].empty())
            m[cuisine].erase(rating);
        m[cuisine][newRating].insert(food);
    }

    string highestRated(string cuisine)
    {
        if (m.count(cuisine))
            return *(rbegin(m[cuisine])->second.begin());
        return "";
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */

int main()
{
    // Solution sol;
    // int r;

    // cout << r << endl;
}