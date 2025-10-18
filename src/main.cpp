#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <chrono>
#include <fstream>
using namespace std;

bool canCreateNote(const string& note, const vector<string>& articles) {
    unordered_map<char, int> availableChars;
    for (const string& article : articles) {
        for (char c : article) {
            if (isspace(c)) continue;
            c = tolower(c);
            availableChars[c]++;
        }
    }
    for (char c : note) {
        if (isspace(c)) continue;
        c = tolower(c);
        if (availableChars[c] <= 0) return false;
        availableChars[c]--;
    }
    return true;
}

string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: cannot open " << filename << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <source_file> <target_file>" << endl;
        return 1;
    }

    string source = readFile(argv[1]);
    string target = readFile(argv[2]);

    auto start = chrono::high_resolution_clock::now();
    bool result = canCreateNote(target, {source});
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "\nCan create " << argv[2] << " from " << argv[1] << "? " << boolalpha << result << endl;
    cout << "Time taken: " << elapsed.count() << " seconds\n";
}