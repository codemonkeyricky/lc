
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file 'input.txt'." << std::endl;
        return 1;
    }

    std::vector<int> a;
    std::vector<int> b;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream stream(line);
        int value1, value2;
        if (stream >> value1 >> value2) {
            a.push_back(value1);
            b.push_back(value2);
        } else {
            std::cerr << "Error: Invalid line format: " << line << std::endl;
        }
    }

    inputFile.close();

    unordered_map<int, int> cnt;

    for (auto& bb : b) {
        ++cnt[bb];
    }

    int rv = 0;
    for (auto& aa : a) {
        rv += aa * cnt[aa];
    }

    cout << rv << endl;

    return 0;
}
