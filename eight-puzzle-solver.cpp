#include "eight-puzzle-solver.h"
#include <thread>

using namespace std;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::steady_clock;

EightPuzzleSolver::EightPuzzleSolver(WINDOW *_window, const string &path):
    total(0),
    current(0),
    precentage(0.0d),
    printLine(3),
    range(pair<size_t,size_t>(3,20)),
    window(_window),
    splitDepth(5)
{
    outFile.open(path);
    if(!outFile.is_open()) {
        throw new exception();
    }
    this->symbols="8+-*/";
}

EightPuzzleSolver::~EightPuzzleSolver()
{
    outFile.close();
}

bool EightPuzzleSolver::initialize(const size_t &start, const size_t &end)
{
    if(start < end && start > 0) {
        this->range.first = start;
        this->range.second = end;
        return true;
    }
    else {
        return false;
    }
}

void EightPuzzleSolver::start()
{
    for (size_t length = this->range.second; length> this->range.first; --length) {
        wmove(window, 0, 0);
        total = pow(5.0,length);
        current = 0;
        precentage = 0.0;
        wprintw(window, "Checking strings of length: %d",length);
        wmove(window, 1, 0);
        wprintw(window, "Total: %.0lf",pow(5.0,length));
        string input(length,'8');
        this->startTime = steady_clock::now();
        permutation(input,0);
    }
}

void EightPuzzleSolver::setThreadCount(const size_t& count)
{
    this->splitDepth = count;
}

std::vector<string> EightPuzzleSolver::getResults()
{
    return this->results;
}

bool EightPuzzleSolver::check(const string &inputs)
{
    while(!evaluation.empty()) {
        evaluation.pop();
    }
    for(const auto& n: inputs) {
        int n1, n2;
        switch (n) {
        case '+': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                evaluation.push(n2+n1);
            }
            break;
        case '-': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                evaluation.push(n2-n1);
            }
            break;
        case '*': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                evaluation.push(n2*n1);
            }
            break;
        case '/': {
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n1 = evaluation.top();
                    evaluation.pop();
                }
                if(evaluation.empty()) {
                    return false;
                }
                else {
                    n2 = evaluation.top();
                    evaluation.pop();
                }
                if(n1==0) {
                    return false;
                }
                else {
                    evaluation.push(n2/n1);
                }
            }
            break;
        case '8':
            evaluation.push(8);
            break;
        default:
            return false;
            break;
        }
    }
    return (evaluation.size()==1 && evaluation.top()==1000);
}

void EightPuzzleSolver::permutation(string &input, size_t index)
{
    if(index==input.size()) {
        this->guard.lock();
        steady_clock::time_point now = steady_clock::now();
        auto ticks = now-this->startTime;
        auto s = duration_cast<chrono::seconds>(ticks).count()%60;
        auto m = duration_cast<chrono::minutes>(ticks).count()%60;
        auto h = duration_cast<chrono::hours>(ticks).count();
        auto ms = duration_cast<chrono::milliseconds>(ticks).count();
        wmove(window, 2, 0);
        ++current;
        precentage = 100.0*static_cast<double>(current)/total;
        std::chrono::milliseconds predict(static_cast<int>(100*ms/precentage));
        wprintw(window, "Elapsed Time: %dh:%dm:%ds, Remaining Time: %04dh:%02dm:%02ds, Progress: %d of %.0lf (%.4f%%) sample: %s",
                h,m,s,
                duration_cast<std::chrono::hours>(predict).count(),
                duration_cast<std::chrono::minutes>(predict).count()%60,
                duration_cast<std::chrono::seconds>(predict).count()%60,
                current,total,precentage,input.c_str());
        wrefresh(window);
        if(check(input)) {
            wmove(window, printLine, 0);
            wprintw(window, "%d: %s",results.size()+1,input.c_str());
            results.push_back(input);
            outFile << input << std::endl;
            wrefresh(window);
            ++printLine;
        }
        this->guard.unlock();
        return;
    }
    else if (index == this->splitDepth) {
        vector<thread> threads;
        for (char symbol : this->symbols) {
            input[index] = symbol;
            threads.emplace_back([=] {
                string cpy(input);
                permutation(cpy, index+1);
            });
        }
        for (thread& t: threads) {
            t.join();
        }
    }
    else {
        for (char symbol : this->symbols) {
            input[index] = symbol;
            permutation(input, index+1);
        }
    }
}
