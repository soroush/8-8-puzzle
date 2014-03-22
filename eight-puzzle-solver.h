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
#include <curses.h>

class EightPuzzleSolver
{
public:
    EightPuzzleSolver(WINDOW *_window, const std::string& outFile);
    ~EightPuzzleSolver();
    bool initialize(const size_t &start, const size_t &end);
    void start();
    std::vector<std::string> getResults();
private:
    bool check(const std::vector<char> &inputs);
    void permutation(std::vector<char>::iterator i);
    double total;
    int current;
    double precentage;
    int printLine;
    std::pair<size_t,size_t> range;
    WINDOW* window;
    std::stack<int> evaluation;
    std::vector<char> inputs;
    std::vector<std::string> results;
    std::ofstream outFile;
};

#endif // EIGHTPUZZLESOLVER_H
