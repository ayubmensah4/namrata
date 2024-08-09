#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>

class WordCounter {
public:
    // call function to read the file and store words
    WordCounter() {
        processFile();
        prepareWordList();
    }

    //Saves word counts to "output.txt"
    void writeWordCounts() const {
        std::ofstream outFile("output.txt");
        for (const auto& word : sortedWords) {
            outFile << word.first << ": " << word.second << "\n";
        }
    }

    // Saves word occurrences with line numbers to "output_lines.txt"
    void writeWordOccurrences() const {
        std::ofstream outFile("output_lines.txt");
        for (const auto& word : wordLines) {
            outFile << word.first << ": ";
            bool first = true;
            for (int lineNum : word.second) {
                if (!first) outFile << ", ";
                outFile << lineNum;
                first = false;
            }
            outFile << "\n";
        }
    }

private:
    std::string inputFile = "input.txt"; 
    std::map<std::string, int> wordCounts;
    std::map<std::string, std::set<int>> wordLines;
    std::vector<std::pair<std::string, int>> sortedWords;

    // Read the file
    void processFile() {
        std::ifstream inFile(inputFile);
        std::string line;
        int lineNum = 0;

        while (std::getline(inFile, line)) {
            lineNum++;
            std::set<std::string> uniqueWords;
            std::istringstream stream(line);
            std::string word;

            while (stream >> word) {
                uniqueWords.insert(word);
            }

            for (const auto& w : uniqueWords) {
                wordCounts[w]++;
                wordLines[w].insert(lineNum);
            }
        }
    }

    // Prepare the list of words sorted by frequency
    void prepareWordList() {
        for (const auto& wc : wordCounts) {
            sortedWords.push_back(wc);
        }

        std::sort(sortedWords.begin(), sortedWords.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return b.second > a.second;
                  });
    }
};

int main() {
    WordCounter wc;

    wc.writeWordCounts();       // Save the word counts to file
    wc.writeWordOccurrences();  // Save the word occurrences to another file

    return 0;
}
