#ifndef EIGHTPUZZLESOLVER_H
#define EIGHTPUZZLESOLVER_H

#include <iomanip>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <ctime>
#include <utility>
#include <fstream>
#include <mutex>
#include <ctime>
#include <chrono>
#include <curses.h>

class EightPuzzleSolver
{
public:
    EightPuzzleSolver(WINDOW *_window, const std::string& outFile);
    ~EightPuzzleSolver();
    bool initialize(const size_t &start, const size_t &end);
    void start();
    void setThreadCount(const size_t&);
    std::vector<std::string> getResults();
private:
    bool check(const std::string &inputs);
    void permutation(std::string &input, size_t index);
    double total;
    int current;
    double precentage;
    uint printLine;
    std::pair<size_t,size_t> range;
    WINDOW* window;
    std::stack<int> evaluation;
    std::string symbols;
    std::vector<std::string> results;
    std::ofstream outFile;
    size_t splitDepth;
    std::mutex guard;
    // Timing
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point elapsedTime;
    std::chrono::system_clock::time_point endTime;
};

#endif // EIGHTPUZZLESOLVER_H
