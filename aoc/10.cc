#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> dp;

int dfs(vector<vector<int>>& mat, int i, int j, int kk,
        set<array<int, 2>>& seen) {

    if (mat[i][j] != kk)
        return 0;

    if (kk == 9) {

        if (!seen.count({i, j})) {
            seen.insert({i, j});
            return 1;
        }

        return 0;
    }

    int m = mat.size();
    int n = mat[0].size();

    int rv = 0;
    vector<int> offset = {0, -1, 0, 1, 0};
    for (auto k = 0; k < 4; ++k) {
        auto ni = i + offset[k + 0];
        auto nj = j + offset[k + 1];
        if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
            rv += dfs(mat, ni, nj, kk + 1, seen);
        }
    }
    return rv;
}

int trailHeads(vector<vector<int>>& mat) {

    int m = mat.size();
    int n = mat[0].size();

    dp = vector<vector<int>>(m, vector<int>(n));

    int rv = 0;
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            if (mat[i][j] == 0) {
                set<array<int, 2>> seen;
                rv += dfs(mat, i, j, 0, seen);
            }
        }
    }
    return rv;
}

int main() {
    std::ifstream inputFile("input.txt"); // Replace with your .txt filename
    std::vector<std::vector<int>> data;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<int> row;
        for (char ch : line) {
            if (std::isdigit(ch)) {
                row.push_back(ch - '0'); // Convert char to int
            }
        }
        data.push_back(row);
    }

    inputFile.close();

    cout << trailHeads(data) << endl;

    return 0;
}
